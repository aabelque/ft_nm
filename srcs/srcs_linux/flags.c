/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:24:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/28 13:56:02 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char			get_flags_ppc(t_elf_symbol sym, t_elf_section *sections) {

	if (sym.shndx > MAX_SECTIONS || sym.shndx == SHN_ABS)
		return (sym.bind == STB_LOCAL ? 'a' : 'A');
	/* prints(sections[sym.shndx].name); */
	/* prints(" -->  "); */
	/* ft_putnbr(sections[sym.shndx].flag); */
	/* prints(" "); */
	/* ft_putnbr(SHF_ALLOC | SHF_WRITE); */
	/* prints(" "); */
	/* /1* ft_putnbr((sections[sym.shndx].flag & SHF_MASKOS) | SHF_ALLOC); *1/ */
	/* prints(" "); */
	/* ft_putnbr((sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE)); */
	/* prints(" "); */
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
	/* 	else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE | SHF_EXECINSTR)) */
	/* 		return (sym.bind == STB_LOCAL ? 't' : 'T'); */
	/* 	else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_MERGE)) */
	/* 		return (sym.bind == STB_LOCAL ? 'r' : 'R'); */
		else if (sections[sym.shndx].flag == SHF_ALLOC) {
			if (sym.bind == STB_WEAK) {
				if (sym.type == STT_OBJECT)
					return (sym.shndx == SHN_UNDEF ? 'v' : 'V');
			}
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		}
	/* 	else if (sections[sym.shndx].flag == ((sections[sym.shndx].flag & SHF_MASKOS) | SHF_ALLOC)) */
	/* 		return (sym.bind == STB_LOCAL ? 'r' : 'R'); */
	/* 	else if (sections[sym.shndx].flag == ((sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE))) */
	/* 		return (sym.bind == STB_LOCAL ? 'g' : 'G'); */
	}
	/* else if (sections[sym.shndx].type == SHT_DYNAMIC) { */
	/* 	if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE)) */
	/* 		return (sym.bind == STB_LOCAL ? 'd' : 'D'); */
	/* 	if (sections[sym.shndx].flag == SHF_ALLOC) */
	/* 		return (sym.bind == STB_LOCAL ? 'r' : 'R'); */
	/* } */
	/* else if (sections[sym.shndx].type == SHT_INIT_ARRAY */
	/* 		|| sections[sym.shndx].type == SHT_FINI_ARRAY) { */
	/* 	if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE)) */
	/* 		return (sym.bind == STB_LOCAL ? 't' : 'T'); */
	/* } */
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
	/* 	else if (sections[sym.shndx].flag == (sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE)) */
	/* 		if (sym.type == STT_OBJECT) */
	/* 			return (sym.bind == STB_LOCAL ? 'B' : 'S'); */
	/* 		return (sym.bind == STB_LOCAL ? 's' : 'S'); */
	}
	/* else if (sections[sym.shndx].type == SHT_NOTE) */
	/* 	return (sym.bind == STB_LOCAL ? 'r' : 'R'); */
	return ('?');
}

char			get_flags(t_elf_symbol sym, t_elf_section *sections) {

	if (sym.shndx > MAX_SECTIONS || sym.shndx == SHN_ABS)
		return (sym.bind == STB_LOCAL ? 'a' : 'A');
	/* prints(sections[sym.shndx].name); */
	/* prints(" -->  "); */
	/* ft_putnbr(sections[sym.shndx].flag); */
	/* prints(" "); */
	/* ft_putnbr(SHF_ALLOC | SHF_WRITE); */
	/* prints(" "); */
	/* /1* ft_putnbr((sections[sym.shndx].flag & SHF_MASKOS) | SHF_ALLOC); *1/ */
	/* prints(" "); */
	/* ft_putnbr((sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE)); */
	/* prints(" "); */
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
				if (sym.type == STT_OBJECT)
					return (sym.shndx == SHN_UNDEF ? 'G' : 'D');
			}
			return (sym.bind == STB_LOCAL ? 'd' : 'D');
		}
		else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE | SHF_EXECINSTR))
			return (sym.bind == STB_LOCAL ? 't' : 'T');
		else if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_MERGE))
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		else if (sections[sym.shndx].flag == SHF_ALLOC) {
			if (sym.bind == STB_WEAK) {
				if (sym.type == STT_OBJECT)
					return (sym.shndx == SHN_UNDEF ? 'v' : 'V');
			}
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		}
		else if (sections[sym.shndx].flag == ((sections[sym.shndx].flag & SHF_MASKOS) | SHF_ALLOC))
			return (sym.bind == STB_LOCAL ? 'r' : 'R');
		else if (sections[sym.shndx].flag == ((sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE)))
			return (sym.bind == STB_LOCAL ? 'g' : 'G');
	}
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
	else if (sections[sym.shndx].type == SHT_NOBITS) {
		if (sections[sym.shndx].flag == (SHF_ALLOC | SHF_WRITE)) {
			if (sym.type == STT_OBJECT)
				return (sym.bind == STB_LOCAL ? 'V' : (sym.bind == STB_GLOBAL) ? 'B' : 'V');
			return (sym.bind == STB_LOCAL ? 'b' : 'B');
		}
		else if (sections[sym.shndx].flag == (sections[sym.shndx].flag & SHF_MASKPROC) | (SHF_ALLOC | SHF_WRITE))
			if (sym.type == STT_OBJECT)
				return (sym.bind == STB_LOCAL ? 'B' : 'S');
			return (sym.bind == STB_LOCAL ? 's' : 'S');
	}
	else if (sections[sym.shndx].type == SHT_NOTE)
		return (sym.bind == STB_LOCAL ? 'r' : 'R');
	return ('?');
}
