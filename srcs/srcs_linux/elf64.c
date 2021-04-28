/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/28 11:37:08 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static short rev = 0;

static inline t_elf_symbol	init_symbols(Elf64_Sym sym, t_elf_symbol symbols, char *symstr) {
	symbols.type = ELF64_ST_TYPE(REV(sym.st_info, rev));
	symbols.bind = ELF64_ST_BIND(REV(sym.st_info, rev));
	symbols.name = symstr + REV(sym.st_name, rev);
	symbols.shndx = REV(sym.st_shndx, rev);
	symbols.value = REV(sym.st_value, rev);
	return (symbols);
}

static inline void			print_symbols(t_elf_symbol symbols, t_elf_section *sections) {
	char			c;

	c = get_flags(symbols, sections);
	if (c == '0')
		return ;
	if (symbols.shndx == SHN_UNDEF)
		write(1, "                ", 16);
	else
		hexdump(symbols.value, 16, 16);
	write(1, " ", 1);
	write(1, &c, 1);
	/* write(1, " ", 1); */
	/* ft_putnbr(symbols.bind); */
	/* write(1, " ", 1); */
	/* ft_putnbr(symbols.type); */
	/* write(1, " ", 1); */
	/* ft_putnbr(symbols.shndx); */
	write(1, " ", 1);
	prints(symbols.name);
	write(1, "\n", 1);
}

static int			print_symelf(Elf64_Sym *sym, Elf64_Shdr *sh, Elf64_Ehdr *eh, int idx, t_elf_section *sections) {
	char			*symstr_table;
	int				symcnt, i, j = 0;
	t_elf_symbol	*symbols = NULL;

	symcnt = REV(sh[idx].sh_size, rev) / REV(sh[idx].sh_entsize, rev);
	symstr_table = (char *)((char *)eh + REV(sh[REV(sh[idx].sh_link, rev)].sh_offset, rev));
	symbols = malloc(sizeof(t_elf_symbol) * symcnt);
	if (!symbols)
		return (ft_perror("Malloc symbols fail\n", 0));
	for (i = 0; i < symcnt; i++) {
		if (sym[i].st_name != 0 && ELF64_ST_TYPE(REV(sym[i].st_info, rev)) != STT_FILE
				&& ELF64_ST_TYPE(REV32(sym[i].st_info, rev)) != STT_SECTION) {
			symbols[j] = init_symbols(sym[i], symbols[j], symstr_table);
			j++;
		}
	}
	ft_qsort_symelf(symbols, 0, j - 1, ft_strcmp);
	for (i = 0; i < j; i++) {
		print_symbols(symbols[i], sections);
	}
	free(symbols);
	return (EXIT_SUCCESS);
}

static t_elf_section	*get_elfsection(char *strtable, Elf64_Shdr *sh, int shnum) {
	int				i;
	t_elf_section	*sections = NULL;

	sections = malloc(sizeof(t_elf_section) * shnum);
	if (!sections)
		return (NULL);
	for (i = 1; i < shnum; i++) {
		sections[i].name = strtable + REV(sh[i].sh_name, rev);
		sections[i].type = REV(sh[i].sh_type, rev);
		sections[i].flag = REV(sh[i].sh_flags, rev);
	}
	return (sections);
}

int			elf64(char *ptr, char *offset, int opt) {
	short			endianess = 0, no_sym = 1;
	char			*strtable;
	Elf64_Ehdr		*eh;
	Elf64_Shdr		*sh;
	t_elf_section	*sections = NULL;

	eh = (Elf64_Ehdr *)ptr;
	endianess = (eh->e_ident[EI_DATA] == ELFDATA2LSB) ? LITTLE : BIG;
	rev = should_reverse(endianess, get_endianess());
	sh = (Elf64_Shdr *)(ptr + REV(eh->e_shoff, rev));
	strtable = ptr + REV(sh[REV(eh->e_shstrndx, rev)].sh_offset, rev);
	if (!(sections = get_elfsection(strtable, sh, REV(eh->e_shnum, rev))))
		return (ft_perror("Malloc sections fail\n", 0));
	for (int i = 0; i < REV(eh->e_shnum, rev); i++) {
		if (opt) {
			if (REV(sh[i].sh_type, rev) == SHT_DYNSYM) {
				if (print_symelf((Elf64_Sym *)((char *)eh + REV(sh[i].sh_offset, rev)), sh, eh, i, sections))
					return (EXIT_FAILURE);
				no_sym = 0;
			}
		}
		else if (REV(sh[i].sh_type, rev) == SHT_SYMTAB) {
			if (print_symelf((Elf64_Sym *)((char *)eh + REV(sh[i].sh_offset, rev)), sh, eh, i, sections))
				return (EXIT_FAILURE);
			no_sym = 0;
		}
	}
	if (no_sym)
		return (ft_perror("No symbols\n", 0));
	free(sections);
	return (EXIT_SUCCESS);
}
