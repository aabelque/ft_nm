/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:19:51 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/30 21:59:15 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			print_symbol32(t_symbol symbol)
{
	if (symbol.n_type == N_UNDF || symbol.n_type == N_INDR)
	{
		write(1, "        ", 8);
		if (symbol.n_type == N_UNDF)
		{
			symbol.ext ? prints(" U ") : prints(" u ");
			prints(symbol.name);
			write(1, "\n", 1);
		}
		else if (symbol.n_type == N_INDR)
		{
			symbol.ext ? prints(" I ") : prints(" i ");
			prints(symbol.name);
			prints(" (indirect for ");
			prints(symbol.name);
			write(1, ")\n", 2);
			return ;
		}
	}
	else if (symbol.n_type == N_SECT || symbol.n_type == N_ABS)
	{
		hexdump(ppc32(symbol.n_value), 16, 8);
		if (symbol.n_sect == sections()->text)
			symbol.ext ? prints(" T ") : prints(" t ");
		else if (symbol.n_type == N_ABS)
			symbol.ext ? prints(" A ") : prints(" a ");
		else if (symbol.n_sect == sections()->data)
			symbol.ext ? prints(" D ") : prints(" d ");
		else if (symbol.n_sect == sections()->bss)
			symbol.ext ? prints(" B ") : prints(" b ");
		else
			symbol.ext ? prints(" S ") : prints(" s ");
		prints(symbol.name);
		write(1, "\n", 1);
	}
}

static void		get_section32(void *ptr, struct segment_command *seg, void *offset)
{
	int					i;
	struct section		*sect;

	sect = (void *)seg + sizeof(*seg);
	for (i = 0; i < ppc32(seg->nsects); i++)
	{
		if (!ft_strcmp(sect[i].sectname, SECT_TEXT)
				&& !ft_strcmp(sect[i].segname, SEG_TEXT))
			sections()->text = sections()->index + 1;
		else if (!ft_strcmp(sect[i].sectname, SECT_DATA)
				&& !ft_strcmp(sect[i].segname, SEG_DATA))
			sections()->data = sections()->index + 1;
		else if (!ft_strcmp(sect[i].sectname, SECT_BSS)
				&& !ft_strcmp(sect[i].segname, SEG_DATA))
			sections()->bss = sections()->index + 1;
		sections()->index++;
	}
}

static int		print_nm32(struct symtab_command *sym, void *ptr, void *offset)
{
	int						i, j;
	char					*stringtable;
	struct nlist			*nlst;
	t_symbol				*symbols;

	nlst = ptr + ppc32(sym->symoff);
	stringtable = ptr + ppc32(sym->stroff);
	symbols = (t_symbol *)malloc(sizeof(t_symbol) * ppc32(sym->nsyms));
	if (check_offset(ptr + ppc32(sym->symoff), offset)
			|| check_offset(ptr + ppc32(sym->stroff), offset))
		return (ft_perror("Corrupted file\n", 0));
	for (i = 0, j = 0; i < ppc32(sym->nsyms); i++)
	{
		if (!(nlst[i].n_type & N_STAB))
		{
			if (check_offset(stringtable
						+ ppc32(nlst[i].n_un.n_strx), offset))
				return (ft_perror("Corrupted file\n", 0));
			symbols[j].name = stringtable + ppc32(nlst[i].n_un.n_strx);
			symbols[j].n_value = nlst[i].n_value;
			symbols[j].n_type = nlst[i].n_type & N_TYPE;
			symbols[j].ext = nlst[i].n_type & N_EXT;
			symbols[j].n_sect = nlst[i].n_sect;
			j++;
		}
	}
	ft_qsort_symbol(symbols, 0, j - 1, ft_strcmp);
	for (i = 0; i < j; i++)
		print_symbol32(symbols[i]);
	free(symbols);
	return (EXIT_SUCCESS);
}

int			handle_32(void *ptr, void *offset)
{
	short					sym;
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;

	sym = 0;
	header = (struct mach_header *)ptr;
	lc = ptr + sizeof(*header);
	set_ppc(swap32(header->cputype) == CPU_TYPE_POWERPC);
	ncmds = ppc32(header->ncmds);
	if (check_offset(ptr + sizeof(*header), offset))
		return (ft_perror("Corrupted file\n", 0));
	for (i = 0; i < ncmds; i++)
	{
		if (check_offset(lc, offset))
			return (ft_perror("Corrupted\n", 0));
		if (ppc32(lc->cmd) == SEGMENT32)
			get_section32(ptr, (struct segment_command *)lc, offset);
		if (ppc32(lc->cmd) == SYMTAB)
		{
			if (print_nm32((struct symtab_command *)lc, ptr, offset))
				return (EXIT_FAILURE);
			sym = 1;
		}
		lc = (void *)lc + ppc32(lc->cmdsize);
	}
	if (!sym)
		return (ft_perror("no symbols\n", 0));
	return (EXIT_SUCCESS);
}
