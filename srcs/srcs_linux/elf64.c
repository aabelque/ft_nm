/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/08 11:43:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
		{
			ft_putnbr(ph->p_type);
			write(1, "\n", 1);
		}
		if (ph->p_type == PT_LOAD)
		{
			ft_putnbr(ph->p_type);
			write(1, "\n", 1);
		}
	}

	
	return (EXIT_SUCCESS);
}
