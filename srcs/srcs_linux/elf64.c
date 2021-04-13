/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/13 17:38:47 by aabelque         ###   ########.fr       */
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

/* static inline void	print_symelf(Elf64_Sym *sym) */
/* { */
/* 	char		*str, *strtable; */
/* 	int			ndx; */
/* 	Elf64_Sym	*sym; */

/* 	sym = (Elf64_Sym *)sh[idx]; */
/* 	ndx = sh[idx].sh_link; */
/* 	strtable = (char *)sh[ndx]; */
/* 	int count = sh[idx].sh_size / sizeof(Elf64_Sym); */

/* 	for (int i = 0; i < count; i++) */
/* 	{ */
/* 		prints(strtable + sym[i].st_name); */
/* 		write(1, "\n", 1); */
/* 	} */
/* } */

int			elf64(char *ptr, char *offset)
{
	short		lendian = 0;
	int			load_offset, symcnt;
	char		*names = NULL;
	Elf64_Ehdr	*eh;
	Elf64_Shdr	*sh;
	char		*strtb;
	Elf64_Sym	*sym;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	for (int i = 0; i < eh->e_shnum; i++)
	{
		sh = get_elfsection(eh, i);
		names = get_strname(eh, sh->sh_name);
		prints(names);
		write(1, "\n", 1);
		if (sh[i].sh_type == SHT_SYMTAB)
		{
			sym = (Elf64_Sym *)((char *)eh + sh[i].sh_offset);
			symcnt = sh[i].sh_size / sizeof(Elf64_Sym);
		}
		if (sh[i].sh_type == SHT_STRTAB)
			strtb = (char *)eh + sh[i].sh_offset;
	}
	for (int i = 0; i < symcnt; i++)
	{
		prints(strtb + sym[i].st_name);
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
