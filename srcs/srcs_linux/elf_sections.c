/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:30:43 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/16 11:32:35 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


inline Elf64_Shdr	*get_shdr(Elf64_Ehdr *eh) {
	return ((Elf64_Shdr *)((char *)eh + eh->e_shoff));
}

inline Elf64_Shdr	*get_elfsection(Elf64_Ehdr *eh, int idx) {
	return (&get_shdr(eh)[idx]);
}

inline char			*get_strtable(Elf64_Ehdr *eh) {

	if (eh->e_shstrndx == SHN_UNDEF)
		return (NULL);
	return ((char *)eh + get_elfsection(eh, eh->e_shstrndx)->sh_offset);
}

inline char			*get_strname(Elf64_Ehdr *eh, int offset) {
	
	char	*strtable;

	strtable = get_strtable(eh);
	if (!strtable)
		return (NULL);
	return (strtable + offset);
}
