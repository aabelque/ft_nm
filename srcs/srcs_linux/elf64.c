/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/07 15:28:28 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			elf64(char *ptr, char *offset)
{
	short				lendian = 0;
	Elf64_Ehdr			*header;
	Elf64_Shdr			*sect;

	header = (Elf64_Ehdr *)ptr;
	if (header->e_ident[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	sect = (void *)header + (header->e_shoff);
	prints(ptr + sect->sh_offset);

	
	return (EXIT_SUCCESS);
}
