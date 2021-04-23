/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/23 16:00:20 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static short rev = 0;

static inline char	get_flags(t_elf_symbol sym, t_elf_section *sections) {

	/* prints(sections[sym.shndx].name); */
	/* prints(" -->  "); */
	if (sym.shndx > MAX_SECTIONS)
		return ('A');
	if (sections[sym.shndx].name == NULL) {
		if (sym.bind == STB_WEAK) {
			if (sym.type == STT_OBJECT)
				return ('v');
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		}
		if (sym.shndx == SHN_UNDEF)
			return (sym.bind == STB_WEAK ? 'w' : 'U');
	}
	else if (!ft_strcmp(sections[sym.shndx].name, ".dynamic")
			|| !ft_strcmp(sections[sym.shndx].name, ".got")
			|| !ft_strcmp(sections[sym.shndx].name, ".got.plt")
			|| !ft_strcmp(sections[sym.shndx].name, ".ctors")
			|| !ft_strcmp(sections[sym.shndx].name, ".data")
			|| !ft_strcmp(sections[sym.shndx].name, ".data.rel.ro")
			) {
		if (sym.bind == STB_WEAK)
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		return (sym.bind == STB_LOCAL ? 'd' : 'D');
	}
	else if (!ft_strcmp(sections[sym.shndx].name, ".rodata")
			|| !ft_strcmp(sections[sym.shndx].name, ".eh_frame")
			|| !ft_strcmp(sections[sym.shndx].name, ".eh_frame_hdr")
			)
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	else if (!ft_strcmp(sections[sym.shndx].name, ".bss")) {
		if (sym.bind == STB_WEAK && sym.type == STT_OBJECT)
			return ('V');
		return (sym.bind == STB_LOCAL ? 'b' : 'B');
	}
	else if (!ft_strcmp(sections[sym.shndx].name, ".text")
			|| !ft_strcmp(sections[sym.shndx].name, ".fini_array")
			|| !ft_strcmp(sections[sym.shndx].name, ".fini")
			|| !ft_strcmp(sections[sym.shndx].name, ".init")
			|| !ft_strcmp(sections[sym.shndx].name, ".init_array")
			) {
		if (sym.bind == STB_WEAK)
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		return (sym.bind == STB_LOCAL ? 't' : 'T');
	}
	else if (!ft_strcmp(sections[sym.shndx].name, ".sbss"))
		return (sym.bind == STB_LOCAL ? 's' : 'S');
	else if (!ft_strcmp(sections[sym.shndx].name, ".sdata"))
		return (sym.bind == STB_LOCAL ? 'g' : 'G');
	return ('?');
}

static inline int	print_symelf(Elf64_Sym *sym, Elf64_Shdr *sh, Elf64_Ehdr *eh, int idx, t_elf_section *sections) {
	char			c;
	char			*symstr_table;
	int				symcnt, i, j = 0;
	t_elf_symbol	*symbols = NULL;

	symcnt = REV(sh[idx].sh_size, rev) / REV(sh[idx].sh_entsize, rev);
	symstr_table = (char *)((char *)eh + REV(sh[REV(sh[idx].sh_link, rev)].sh_offset, rev));
	symbols = malloc(sizeof(t_elf_symbol) * symcnt);
	if (!symbols)
		return (ft_perror("Malloc symbols fail\n", 0));
	for (i = 0; i < symcnt; i++) {
		if (sym[i].st_name != 0 && ELF64_ST_TYPE(REV(sym[i].st_info, rev)) != STT_FILE) {
			symbols[j].type = ELF64_ST_TYPE(REV(sym[i].st_info, rev));
			symbols[j].bind = ELF64_ST_BIND(REV(sym[i].st_info, rev));
			symbols[j].name = symstr_table + REV(sym[i].st_name, rev);
			symbols[j].shndx = REV(sym[i].st_shndx, rev);
			symbols[j].value = REV(sym[i].st_value, rev);
			j++;
		}
	}
	ft_qsort_symelf(symbols, 0, j - 1, ft_strcmp);
	for (i = 0; i < j; i++) {
		c = get_flags(symbols[i], sections);
		if (symbols[i].shndx == SHN_UNDEF)
			write(1, "                ", 16);
		else
			hexdump(symbols[i].value, 16, 16);
		write(1, " ", 1);
		write(1, &c, 1);
		/* write(1, " ", 1); */
		/* ft_putnbr(symbols[i].bind); */
		/* write(1, " ", 1); */
		/* ft_putnbr(symbols[i].shndx); */
		write(1, " ", 1);
		prints(symbols[i].name);
		write(1, "\n", 1);
	}
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
		if (REV(sh[i].sh_type, rev) == SHT_SYMTAB) {
			if (print_symelf((Elf64_Sym *)((char *)eh + REV(sh[i].sh_offset, rev)), sh, eh, i, sections))
				return (EXIT_FAILURE);
			no_sym = 0;;
		}
		else if (opt) {
			write(1, "x", 1);
			if (REV(sh[i].sh_type, rev) == SHT_DYNSYM) {
				if (print_symelf((Elf64_Sym *)((char *)eh + REV(sh[i].sh_offset, rev)), sh, eh, i, sections))
					return (EXIT_FAILURE);
			}
		}
	}
	if (no_sym)
		return (ft_perror("No symbols\n", 0));
	return (EXIT_SUCCESS);
}
