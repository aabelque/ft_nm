/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:49:57 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/25 17:42:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static short rev = 0;

static inline t_elf_symbol	init_symbols(Elf32_Sym sym, t_elf_symbol symbols, char *symstr) {
	symbols.type = ELF32_ST_TYPE(REV32(sym.st_info, rev));
	symbols.bind = ELF32_ST_BIND(REV32(sym.st_info, rev));
	symbols.name = symstr + REV32(sym.st_name, rev);
	symbols.shndx = REV32(sym.st_shndx, rev);
	symbols.value = REV32(sym.st_value, rev);
	return (symbols);
}

static inline void			print_symbols(t_elf_symbol symbols, t_elf_section *sections) {
	char			c;

	c = get_flags(symbols, sections);
	if (!c)
		return ;
	if (symbols.shndx == SHN_UNDEF)
		write(1, "        ", 8);
	else
		hexdump(symbols.value, 16, 8);
	write(1, " ", 1);
	write(1, &c, 1);
	/* write(1, " ", 1); */
	/* ft_putnbr(symbols[i].bind); */
	/* write(1, " ", 1); */
	/* ft_putnbr(symbols[i].shndx); */
	write(1, " ", 1);
	prints(symbols.name);
	write(1, "\n", 1);
}

static int			print_symelf(Elf32_Sym *sym, Elf32_Shdr *sh, Elf32_Ehdr *eh, int idx, t_elf_section *sections) {
	char			*symstr_table;
	int				symcnt, i, j = 0;
	t_elf_symbol	*symbols = NULL;

	symcnt = REV32(sh[idx].sh_size, rev) / REV32(sh[idx].sh_entsize, rev);
	symstr_table = (char *)((char *)eh + REV32(sh[REV32(sh[idx].sh_link, rev)].sh_offset, rev));
	symbols = malloc(sizeof(t_elf_symbol) * symcnt);
	if (!symbols)
		return (ft_perror("Malloc symbols fail\n", 0));
	for (i = 0; i < symcnt; i++) {
		if (sym[i].st_name != 0 && ELF32_ST_TYPE(REV32(sym[i].st_info, rev)) != STT_FILE) {
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

static t_elf_section	*get_elfsection(char *strtable, Elf32_Shdr *sh, int shnum) {
	int				i;
	t_elf_section	*sections = NULL;

	sections = malloc(sizeof(t_elf_section) * shnum);
	if (!sections)
		return (NULL);
	for (i = 1; i < shnum; i++) {
		sections[i].name = strtable + REV32(sh[i].sh_name, rev);
	}
	return (sections);
}

int			elf32(char *ptr, char *offset, int opt) {
	short			endianess = 0, no_sym = 1;
	char			*strtable;
	Elf32_Ehdr		*eh;
	Elf32_Shdr		*sh;
	t_elf_section	*sections = NULL;

	eh = (Elf32_Ehdr *)ptr;
	endianess = (eh->e_ident[EI_DATA] == ELFDATA2LSB) ? LITTLE : BIG;
	rev = should_reverse(endianess, get_endianess());
	sh = (Elf32_Shdr *)(ptr + REV32(eh->e_shoff, rev));
	strtable = ptr + REV32(sh[REV32(eh->e_shstrndx, rev)].sh_offset, rev);
	if (!(sections = get_elfsection(strtable, sh, REV32(eh->e_shnum, rev))))
		return (ft_perror("Malloc ections fail\n", 0));
	for (int i = 0; i < REV32(eh->e_shnum, rev); i++) {
		if (opt) {
			if (REV32(sh[i].sh_type, rev) == SHT_DYNSYM) {
				if (print_symelf((Elf32_Sym *)((char *)eh + REV32(sh[i].sh_offset, rev)), sh, eh, i, sections))
					return (EXIT_FAILURE);
				no_sym = 0;
			}
		}
		else if (REV32(sh[i].sh_type, rev) == SHT_SYMTAB) {
			if (print_symelf((Elf32_Sym *)((char *)eh + REV32(sh[i].sh_offset, rev)), sh, eh, i, sections))
				return (EXIT_FAILURE);
			no_sym = 0;
		}
	}
	if (no_sym)
		return (ft_perror("No symbols\n", 0));
	free(sections);
	return (EXIT_SUCCESS);
}
