/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/21 16:53:26 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline char	get_flags(Elf64_Shdr *sh, t_elf_symbol sym, t_elf_section *sections) {

	if (sections[sym.shndx].name == NULL)
		prints("OKK");
	prints(sections[sym.shndx].name);
	write(1, "\n", 1);
	if (sym.shndx > MAX_SECTIONS)
		return ('A');
	if (sym.bind == STB_WEAK)
		return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
	if (sym.shndx == SHN_UNDEF)
		return (sym.bind == STB_WEAK ? 'w' : 'U');
	if (sym.shndx == SHN_ABS)
		return ('A');
	if (sh[sym.shndx].sh_type == SHT_NOBITS
			&& sh[sym.shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return (sym.bind == STB_LOCAL ? 'b' : 'B');
	if (sh[sym.shndx].sh_type == SHT_PROGBITS
			&& sh[sym.shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return (sym.bind == STB_LOCAL ? 'd' : 'D');
	if (sh[sym.shndx].sh_type == SHT_DYNAMIC)
		return (sym.bind == STB_LOCAL ? 'd' : 'D');
	if (sh[sym.shndx].sh_type == SHT_PROGBITS
			&& sh[sym.shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		return (sym.bind == STB_LOCAL ? 't' : 'T');
	if (sh[sym.shndx].sh_type == SHT_PROGBITS
			&& sh[sym.shndx].sh_flags == SHF_ALLOC)
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	if (sh[sym.shndx].sh_type == SHT_INIT_ARRAY
			|| sh[sym.shndx].sh_type == SHT_FINI_ARRAY)
		return (sym.bind == STB_LOCAL ? 't' : 'T');
	/* prints(sh[sym.shndx].sh_name); */
	/* write(1, "\n", 1); */
	/* if (ft_strcmp((const char *)sh[sym.shndx].sh_name, ".sbss")) */
	/* 	return ('S'); */
	return ('?');
}

static inline int	print_symelf(Elf64_Sym *sym, Elf64_Shdr *sh, Elf64_Ehdr *eh, int idx, t_elf_section *sections) {
	char			c;
	char			*symstr_table;
	int				symcnt, i, j = 0;
	t_elf_symbol	*symbols = NULL;

	symcnt = sh[idx].sh_size / sh[idx].sh_entsize;
	symstr_table = (char *)((char *)eh + sh[sh[idx].sh_link].sh_offset);
	symbols = malloc(sizeof(t_elf_symbol) * symcnt);
	if (!symbols)
		return (ft_perror("Malloc symbols fail\n", 0));
	for (i = 0; i < symcnt; i++) {
		if (sym[i].st_name != 0 && ELF64_ST_TYPE(sym[i].st_info) != STT_FILE) {
			symbols[j].type = ELF64_ST_TYPE(sym[i].st_info);
			symbols[j].bind = ELF64_ST_BIND(sym[i].st_info);
			symbols[j].name = symstr_table + sym[i].st_name;
			symbols[j].shndx = sym[i].st_shndx;
			ft_putnbr(symbols[j].shndx);
			write(1, "\n", 1);
			symbols[j].value = sym[i].st_value;
			j++;
		}
	}
	ft_qsort_symelf(symbols, 0, j - 1, ft_strcmp);
	for (i = 0; i < j; i++) {
		c = get_flags(sh, symbols[i], sections);
		if (symbols[i].shndx == SHN_UNDEF)
			write(1, "                ", 16);
		else
			hexdump(symbols[i].value, 16, 16);
		write(1, " ", 1);
		write(1, &c, 1);
		write(1, " ", 1);
		/* ft_putnbr(symbols[i].bind); */
		/* write(1, " ", 1); */
		ft_putnbr(symbols[i].shndx);
		write(1, " ", 1);
		prints(symbols[i].name);
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}

int			elf64(char *ptr, char *offset) {
	short			lendian = 0;
	char			*strtable;
	Elf64_Ehdr		*eh;
	Elf64_Shdr		*sh;
	t_elf_section	*sections = NULL;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	sh = (Elf64_Shdr *)(ptr + eh->e_shoff);
	strtable = ptr + sh[eh->e_shstrndx].sh_offset;
	sections = malloc(sizeof(t_elf_section) * eh->e_shnum);
	if (!sections)
		return (ft_perror("Malloc sections fail\n", 0));
	for (int i = 0; i < eh->e_shnum; i++) {
		if (i)
			sections[i].name = strtable + sh[i].sh_name;
		if (sh[i].sh_type == SHT_SYMTAB
				|| sh[i].sh_type == SHT_DYNSYM)
			if (print_symelf((Elf64_Sym *)((char *)eh + sh[i].sh_offset), sh, eh, i, sections))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
