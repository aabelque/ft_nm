/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/17 16:08:06 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline void	print_symelf(Elf64_Sym *sym, Elf64_Shdr *sh, Elf64_Ehdr *eh, int idx) {
	char		*symstr_table;
	int			symcnt, i, j = 0;
	t_symelf	*symbols;

	symcnt = sh[idx].sh_size / sh[idx].sh_entsize;
	symstr_table = (char *)((char *)eh + sh[sh[idx].sh_link].sh_offset);
	symbols = (t_symelf *)malloc(sizeof(t_symelf) * symcnt);
	for (i = 0; i < symcnt; i++) {
		if (sym[i].st_name != 0 && ELF64_ST_TYPE(sym[i].st_info) != STT_FILE) {
			symbols[j].type = ELF64_ST_TYPE(sym[i].st_info);
			symbols[j].bind = ELF64_ST_BIND(sym[i].st_info);
			symbols[j].name = symstr_table + sym[i].st_name;
			symbols[j].shndx = sym[i].st_shndx;
			symbols[j].value = sym[i].st_value;
			j++;
		}
	}
	ft_qsort_symelf(symbols, 0, j - 1, ft_strcmp);
	for (i = 0; i < j; i++) {
		if (symbols[i].shndx == SHN_UNDEF)
			write(1, "                ", 16);
		else
			hexdump(symbols[i].value, 16, 16);
		write(1, " ", 1);
		if (sh[symbols[i].shndx].sh_type == SHT_NOBITS
       && sh[symbols[i].shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			prints("B ");
		ft_putnbr(symbols[i].type);
		write(1, " ", 1);
		ft_putnbr(symbols[i].bind);
		write(1, " ", 1);
		ft_putnbr(symbols[i].shndx);
		write(1, " ", 1);
		prints(symbols[i].name);
		write(1, "\n", 1);
	}
}

int			elf64(char *ptr, char *offset) {
	short		lendian = 0;
	char		*names;
	Elf64_Ehdr	*eh;
	Elf64_Shdr	*sh;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	sh = (Elf64_Shdr *)(ptr + eh->e_shoff);
	names = ptr + sh[eh->e_shstrndx].sh_offset;
	for (int i = 0; i < eh->e_shnum; i++) {
		/* prints(names + sh[i].sh_name); */
		/* write(1, "\n", 1); */
		if (sh[i].sh_type == SHT_SYMTAB)
			print_symelf((Elf64_Sym *)((char *)eh + sh[i].sh_offset), sh, eh, i);
	}
	return (EXIT_SUCCESS);
}
