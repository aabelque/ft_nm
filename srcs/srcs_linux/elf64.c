/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/16 11:50:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
	Elf64_Shdr	*strtb;
	Elf64_Shdr	*symtab;
	Elf64_Sym	*sym;
	char		*str;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	/* sh = (Elf64_Shdr *)(ptr + eh->e_shoff); */
	names = ptr + sh[eh->e_shstrndx].sh_offset;
	for (int i = 0; i < eh->e_shnum; i++)
	{
		sh = get_elfsection(eh, i);
		names = get_strname(eh, sh->sh_name);
		prints(names);
		write(1, "\n", 1);
		if (sh[i].sh_type == SHT_SYMTAB)
		{
			sym = (Elf64_Sym *)((char *)eh + sh[i].sh_offset);
			symcnt = sh[i].sh_size / sh[i].sh_entsize;
			str = (char *)((char *)eh + sh[sh[i].sh_link].sh_offset);
		}
	}
	for (int i = 0; i < symcnt; i++)
	{
		hexdump(sym[i].st_value, 16, 16);
		write(1, " ", 1);
		prints(str + sym[i].st_name);
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
