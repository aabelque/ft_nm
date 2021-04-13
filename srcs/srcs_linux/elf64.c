/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/13 16:06:37 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline Elf64_Shdr	*get_shdr(Elf64_Ehdr *eh) {
	return ((Elf64_Shdr *)((char *)eh + eh->e_shoff));
}

static inline Elf64_Shdr	*get_elfsection(Elf64_Ehdr *eh, int idx)
{
	return (&get_shdr(eh)[idx]);
}

static inline char			*get_strtable(Elf64_Ehdr *eh)
{
	if (eh->e_shstrndx == SHN_UNDEF)
		return (NULL);
	return ((char *)eh + get_elfsection(eh, eh->e_shstrndx)->sh_offset);
}

static inline char			*get_strname(Elf64_Ehdr *eh, int offset)
{
	char	*strtable;

	strtable = get_strtable(eh);
	if (!strtable)
		return (NULL);
	return (strtable + offset);
}

int			elf64(char *ptr, char *offset)
{
	short		lendian = 0;
	int			load_offset;
	char		*strtab = NULL;
	Elf64_Ehdr	*eh;
	Elf64_Shdr	*sh;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	for (int i = 0; i < eh->e_shnum; i++)
	{
		sh = get_elfsection(eh, i);
		if (sh[i].sh_type == SHT_SYMTAB)
		{
			strtab = get_strname(eh, sh->sh_name);
			prints(strtab);
			write(1, "\n", 1);
		}
	}
	return (EXIT_SUCCESS);
}
