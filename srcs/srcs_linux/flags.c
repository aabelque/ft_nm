/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:24:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/27 14:55:15 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			text_flags(t_elf_symbol sym, t_elf_section *sections) {
	return (!ft_strcmp(sections[sym.shndx].name, ".text")
			|| !ft_strcmp(sections[sym.shndx].name, ".bortext")
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
			|| !ft_strcmp(sections[sym.shndx].name, ".HP.preinit")
			);
}

int			rodata_flags(t_elf_symbol sym, t_elf_section *sections) {
	return (!ft_strcmp(sections[sym.shndx].name, ".rodata")
			|| !ft_strcmp(sections[sym.shndx].name, ".rodata_cond")
			|| !ft_strcmp(sections[sym.shndx].name, ".eh_frame")
			|| !ft_strcmp(sections[sym.shndx].name, ".eh_frame_hdr")
			|| !ft_strcmp(sections[sym.shndx].name, ".note.hpux_options")
			);}

char			get_flags(t_elf_symbol sym, t_elf_section *sections) {

	if (sym.shndx > MAX_SECTIONS || sym.shndx == SHN_ABS)
		return (sym.bind == STB_LOCAL ? 'a' : 'A');
	prints(sections[sym.shndx].name);
	prints(" -->  ");
	ft_putnbr(sections[sym.shndx].flag);
	prints(" ");
	ft_putnbr((sections[sym.shndx].flag & SHF_MASKOS) | (SHF_ALLOC | SHF_WRITE));
	prints(" ");
	ft_putnbr((sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE));
	prints(" ");
	if (sections[sym.shndx].name == NULL) {
		if (sym.bind == STB_WEAK) {
			if (sym.type == STT_OBJECT)
				return ('v');
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		}
		if (sym.shndx == SHN_UNDEF)
			return (sym.bind == STB_WEAK ? 'w' : 'U');
	}
	else if (sections[sym.shndx].type == SHT_PROGBITS) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_EXECINSTR)) {
			if (sym.bind == STB_WEAK)
				return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
			return (sym.bind == STB_LOCAL ? 't' : 'T');
		}
		else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE)) {
			if (sym.bind == STB_WEAK) {
				if (sym.type == STT_OBJECT)
					return (sym.shndx == SHN_UNDEF ? 'v' : 'V');
				return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
			}
			return (sym.bind == STB_LOCAL ? 'd' : 'D');
		}
		else if (sections[sym.shndx].flag == SHF_ALLOC) 
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		else if (sections[sym.shndx].flag == sections[sym.shndx].flag & SHF_MASKOS | SHF_ALLOC)
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		else if (sections[sym.shndx].flag == sections[sym.shndx].flag & SHF_MASKPROC | (SHF_ALLOC | SHF_WRITE))
			return (sym.bind == STB_LOCAL ? 'g' : 'G');
	}
	else if (sections[sym.shndx].type == SHT_DYNAMIC) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE))
			return (sym.bind == STB_LOCAL ? 'd' : 'D');
	}
	else if (sections[sym.shndx].type == SHT_INIT_ARRAY
			|| sections[sym.shndx].type == SHT_FINI_ARRAY) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE))
			return (sym.bind == STB_LOCAL ? 't' : 'T');
	}
	/* else if (data_flags(sym, sections)) { */
	/* 	if (sym.bind == STB_WEAK) */
	/* 		return (sym.shndx == SHN_UNDEF ? 'w' : 'W'); */
	/* 	return (sym.bind == STB_LOCAL ? 'd' : 'D'); */
	/* } */
	/* else if (rodata_flags(sym, sections)) { */
	/* 	if (sym.bind == STB_WEAK) */
	/* 		return (sym.bind == STB_LOCAL ? 'd' : 'D'); */
	/* 	return (sym.bind == STB_LOCAL ? 'r' : 'R'); */
	/* } */
	else if (sections[sym.shndx].type == SHT_NOBITS) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE)) {
			if (sym.bind == STB_WEAK && sym.type == STT_OBJECT)
				return ('V');
			return (sym.bind == STB_LOCAL ? 'b' : 'B');
		}
		else if (sections[sym.shndx].flag == sections[sym.shndx].flag | (SHF_ALLOC | SHF_WRITE) & SHF_MASKPROC)
			return (sym.bind == STB_LOCAL ? 's' : 'S');
	}
	return ('?');
}
