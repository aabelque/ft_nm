/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/16 17:23:37 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline void	print_symelf(Elf64_Sym *sym, Elf64_Shdr *sh, Elf64_Ehdr *eh, int idx) {
	char		*symstr_table;
	int			symcnt, i, j = 0;
	t_symbol	*symbols;

	symcnt = sh[idx].sh_size / sh[idx].sh_entsize;
	symstr_table = (char *)((char *)eh + sh[sh[idx].sh_link].sh_offset);
	symbols = (t_symbol *)malloc(sizeof(t_symbol) * symcnt);
	for (i = 0; i < symcnt; i++) {
		if (sym[i].st_name != STN_UNDEF) {
			symbols[i].name = symstr_table + sym[i].st_name;
			symbols[i].n_value = sym[i].st_value;
			j++;
		}
	}
	for (i = 0; i < j; i++) {
		hexdump(symbols[i].n_value, 16, 16);
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
		prints(names + sh[i].sh_name);
		write(1, "\n", 1);
		if (sh[i].sh_type == SHT_SYMTAB)
			print_symelf((Elf64_Sym *)((char *)eh + sh[i].sh_offset), sh, eh, i);
	}
	return (EXIT_SUCCESS);
}
