/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/11 13:37:48 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	get_dynamic_table(char *ptr, Elf64_Dyn *dyn, const char *addr, int	offset)
{
	int			i = 0;
	int			stroffset;
	const char	*straddr = NULL;
	const char	*strtab = NULL;

	while (42)
	{
		if (dyn[i].d_tag == DT_NULL)
			break ;
		if (dyn[i].d_tag == DT_STRTAB)
		{
			straddr = (const char *)dyn[i].d_un.d_ptr;
			stroffset = offset + (straddr - addr);
			strtab = ptr + stroffset;
		}
		i++;
	}
	if (strtab == NULL)
		return (ft_perror("There is no string table\n", 0));
	while (42)
	{
		if (dyn[i].d_tag == DT_NULL)
			break ;
		if (dyn[i].d_tag == DT_NEEDED)
			prints(&strtab[dyn[i].d_un.d_val]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int			elf64(char *ptr, char *offset)
{
	short		lendian = 0;
	int			load_offset;
	const char	*load_addr = NULL;
	Elf64_Ehdr	*eh;
	Elf64_Shdr	*sh;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	sh = (Elf64_Shdr *)((char *)ptr + (eh->e_shoff + eh->e_shentsize * shstrndx));
	if (sh->sh_type == SHT_SYMTAB)
		prints("Yes !!\n");
	return (EXIT_SUCCESS);
}
