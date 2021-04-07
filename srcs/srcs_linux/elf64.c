/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/07 18:15:17 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			elf64(char *ptr, char *offset)
{
	short				lendian = 0;
	Elf64_Ehdr			*header;
	Elf64_Phdr			*program_hdr;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	for (int i = 0; i < header->e_shnum; i++)
	{
		program_hdr = (Elf64_Phdr *)(void *)ptr + (header->e_phoff + header->e_phentsize * i);
		ft_putnbr(swap64(program_hdr->p_type));
	}

	
	return (EXIT_SUCCESS);
}
