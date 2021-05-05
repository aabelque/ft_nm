/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:24:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/05/05 16:17:08 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char			get_flags_ppc(t_elf_symbol sym, t_elf_section *sections) {

	if (sym.shndx > MAX_SECTIONS || sym.shndx == SHN_ABS)
		return (sym.bind == STB_LOCAL ? 'a' : 'A');
	if (sections[sym.shndx].name == NULL) {
		if (sym.bind == STB_WEAK) {
			if (sym.type == STT_OBJECT)
				return ('v');
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		}
		else if (sym.bind == STB_LOCAL && sym.type == STT_NOTYPE)
			return ('0');
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
			else if (sym.bind == STB_GLOBAL) {
				if (sym.type == STT_OBJECT) {
					if (!ft_strcmp(sections[sym.shndx].name, ".sdata"))
						return ('G');
					return ('D');
				}
				else if (sym.type == STT_NOTYPE) {
					if (!ft_strcmp(sections[sym.shndx].name, ".sdata"))
						return ('G');
					return ('D');
				}
			}
			return (sym.bind == STB_LOCAL ? 'd' : 'D');
		}
		else if (sections[sym.shndx].flag == SHF_ALLOC) {
			if (sym.bind == STB_WEAK) {
				if (sym.type == STT_OBJECT)
					return (sym.shndx == SHN_UNDEF ? 'v' : 'V');
			}
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		}
	}
	else if (sections[sym.shndx].type == SHT_NOBITS) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE)) {
			if (sym.type == STT_OBJECT) {
				if (sym.bind == STB_GLOBAL) {
					if (!ft_strcmp(sections[sym.shndx].name, ".sbss"))
						return ('S');
					return ('B');
				}
				else if (sym.bind == STB_WEAK)
					return ('V');
			}
			if (!ft_strcmp(sections[sym.shndx].name, ".sbss"))
				return ('S');
			return (sym.bind == STB_LOCAL ? 'b' : 'B');
		}
	}
	return ('?');
}

char			get_flags(t_elf_symbol sym, t_elf_section *sections) {

	if (sym.shndx > MAX_SECTIONS || sym.shndx == SHN_ABS)
		return (sym.bind == STB_LOCAL ? 'a' : 'A');
	if (sections[sym.shndx].name == NULL) {
		if (sym.bind == STB_WEAK) {
			if (sym.type == STT_OBJECT)
				return ('v');
			return (sym.shndx == SHN_UNDEF ? 'w' : 'W');
		}
		else if (sym.bind == STB_LOCAL && sym.type == STT_NOTYPE)
			return ('0');
		if (sym.shndx == SHN_UNDEF)
			return (sym.bind == STB_WEAK ? 'w' : 'U');
	}
	else if (sections[sym.shndx].type == SHT_PROGBITS)
		return (progbits_flag(sym, sections));
	else if (sections[sym.shndx].type == SHT_DYNAMIC) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE))
			return (sym.bind == STB_LOCAL ? 'd' : 'D');
		if (sections[sym.shndx].flag == SHF_ALLOC)
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
	}
	else if (sections[sym.shndx].type == SHT_INIT_ARRAY
			|| sections[sym.shndx].type == SHT_FINI_ARRAY) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE))
			return (sym.bind == STB_LOCAL ? 't' : 'T');
	}
	else if (sections[sym.shndx].type == SHT_NOBITS)
		return (nobits_flag(sym, sections));
	else if (sections[sym.shndx].type == SHT_NOTE)
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	return ('?');
}
