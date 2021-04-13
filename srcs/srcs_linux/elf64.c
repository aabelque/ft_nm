/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/13 13:52:34 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	get_dynamic_table(char *ptr, Elf64_Dyn *dyn, const char *addr, int	offset)
{
	int			i = 0;
	int			stroffset;
	const char	*straddr = NULL;
	const char	*strtab = NULL;

	while (42)
	{
		if (dyn[i].d_tag == DT_NULL)
			break ;
		if (dyn[i].d_tag == DT_STRTAB)
		{
			straddr = (const char *)dyn[i].d_un.d_ptr;
			stroffset = offset + (straddr - addr);
			strtab = ptr + stroffset;
		}
		i++;
	}
	if (strtab == NULL)
		return (ft_perror("There is no string table\n", 0));
	while (42)
	{
		if (dyn[i].d_tag == DT_NULL)
			break ;
		if (dyn[i].d_tag == DT_NEEDED)
			prints(&strtab[dyn[i].d_un.d_val]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int			elf64(char *ptr, char *offset)
{
	short		lendian = 0;
	int			load_offset;
	char		*strtab = NULL;
	Elf64_Ehdr	*eh;
	Elf64_Shdr	*sh;
	Elf64_Sym	*sym;

	eh = (Elf64_Ehdr *)ptr;
	sh = (Elf64_Shdr *)((char *)ptr + eh->e_shoff);
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	ft_putnbr(eh->e_shstrndx);
	write(1, "\n", 1);
	for (int i = 0; i < eh->e_shnum; i++)
	{
		if (sh[i].sh_type == SHT_SYMTAB)
		{
			sym = (Elf64_Sym *)sh[i];
			hexdump(swap64(sym->st_value), 16, 16);
			prints("Symtab\n");
		}
		if (sh[i].sh_type == SHT_DYNAMIC)
			prints("Dynamic\n");
		if (sh[i].sh_type == SHT_STRTAB)
		{
			prints("Strtab\n");
			ft_putnbr(sh->sh_name);
			write(1, "\n", 1);
			strtab = ptr + sh->sh_name;
			prints(strtab);
			write(1, "\n", 1);
		}
		sh = (Elf64_Shdr *)((char *)sh + sh->sh_size);
	}
	return (EXIT_SUCCESS);
}
