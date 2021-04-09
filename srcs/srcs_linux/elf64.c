/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/09 13:17:27 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	get_dynamic_table(Elf64_Dyn *dyn)
{
	int			i = 0;
	const char	*stringtable = NULL;

	while (42)
	{
		if (dyn[i].d_tag == DT_NULL)
			break ;
		if (dyn[i].d_tag == STRTAB)
			stringtable = (const char *)dyn[i].d_un.d_ptr;
		i++;
	}
	if (stringtable == NULL)
		return (ft_perror("There is no string table\n", 0));
	prints(stringtable);
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int			elf64(char *ptr, char *offset)
{
	short				lendian = 0;
	Elf64_Ehdr			*eh;
	Elf64_Phdr			*ph;

	eh = (Elf64_Ehdr *)ptr;
	if (eh->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	for (int i = 0; i < eh->e_shnum; i++)
	{
		ph = (Elf64_Phdr *)((char *)ptr + (eh->e_phoff + eh->e_phentsize * i));
		if (ph->p_type == PT_DYNAMIC)
			if (get_dynamic_table((Elf64_Dyn *)(ptr + ph->p_offset)))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
