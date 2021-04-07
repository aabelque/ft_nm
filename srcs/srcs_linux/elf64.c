/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/07 14:26:29 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			elf64(char *ptr, char *offset)
{
	short				lendian = 0;
	Elf64_Ehdr			*header;

	header = (Elf64_Ehdr *)ptr;
	ft_putnbr(header->e_phnum);
	write(1, "\n", 1);
	ft_putnbr(header->e_shnum);
	write(1, "\n", 1);
	if ((unsigned char)ptr[EI_DATA] == ELFDATA2LSB)
		lendian = 1;
	
	return (EXIT_SUCCESS);
}
