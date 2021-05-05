/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:30:46 by azziz             #+#    #+#             */
/*   Updated: 2021/05/05 15:33:01 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		progbits_flag(t_elf_symbol sym, t_elf_section *sections) {
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
			if (sym.type == STT_OBJECT)
				return (sym.shndx == SHN_UNDEF ? 'G' : 'D');
		}
		else if (sym.bind == STB_LOOS)
			return ('u');
		return (sym.bind == STB_LOCAL ? 'd' : 'D');
	}
	else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE | SHF_EXECINSTR))
		return (sym.bind == STB_LOCAL ? 't' : 'T');
	else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_MERGE))
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_MERGE | SHF_STRINGS))
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	else if (sections[sym.shndx].flag == SHF_ALLOC) {
		if (sym.bind == STB_WEAK) {
			if (sym.type == STT_OBJECT)
				return (sym.shndx == SHN_UNDEF ? 'v' : 'V');
		}
		if (sym.bind == STB_LOOS)
			return ('u');
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	}
	else if (sections[sym.shndx].flag == ((sections[sym.shndx].flag & SHF_MASKOS) | SHF_ALLOC))
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	else if (sections[sym.shndx].flag == ((sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE)))
		return (sym.bind == STB_LOCAL ? 'g' : 'G');
}
