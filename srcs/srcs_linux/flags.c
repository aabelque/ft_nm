/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:24:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/25 17:31:14 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			text_flags(t_elf_symbol sym, t_elf_section *sections) {
	return (!ft_strcmp(sections[sym.shndx].name, ".text")
			|| !ft_strcmp(sections[sym.shndx].name, ".fini_array")
			|| !ft_strcmp(sections[sym.shndx].name, ".fini")
			|| !ft_strcmp(sections[sym.shndx].name, ".init")
			|| !ft_strcmp(sections[sym.shndx].name, ".init_array")
			);
}

int			data_flags(t_elf_symbol sym, t_elf_section *sections) {
	return (!ft_strcmp(sections[sym.shndx].name, ".dynamic")
			|| !ft_strcmp(sections[sym.shndx].name, ".got")
			|| !ft_strcmp(sections[sym.shndx].name, ".got.plt")
			|| !ft_strcmp(sections[sym.shndx].name, ".ctors")
			|| !ft_strcmp(sections[sym.shndx].name, ".data")
			|| !ft_strcmp(sections[sym.shndx].name, ".data.rel.ro")
			);
}

int			rodata_flags(t_elf_symbol sym, t_elf_section *sections) {
	return (!ft_strcmp(sections[sym.shndx].name, ".rodata")
			|| !ft_strcmp(sections[sym.shndx].name, ".eh_frame")
			|| !ft_strcmp(sections[sym.shndx].name, ".eh_frame_hdr")
			);
}

char			get_flags(t_elf_symbol sym, t_elf_section *sections) {

	if (sym.shndx > MAX_SECTIONS)
		return ('A');
	prints(sections[sym.shndx].name);
	prints(" -->  ");
	if (sections[sym.shndx].name == NULL) {
		if (sym.bind == STB_WEAK) {
			if (sym.type == STT_OBJECT)
				return ('v');
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		}
		if (sym.shndx == SHN_UNDEF)
			return (sym.bind == STB_WEAK ? 'w' : 'U');
	}
	else if (data_flags(sym, sections)) {
		if (sym.bind == STB_WEAK)
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		return (sym.bind == STB_LOCAL ? 'd' : 'D');
	}
	else if (rodata_flags(sym, sections))
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	else if (!ft_strcmp(sections[sym.shndx].name, ".bss")) {
		if (sym.bind == STB_WEAK && sym.type == STT_OBJECT)
			return ('V');
		return (sym.bind == STB_LOCAL ? 'b' : 'B');
	}
	else if (text_flags(sym, sections)) {
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
