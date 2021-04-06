/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:22:26 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/06 19:52:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		elf64(char *ptr, char *offset)
{
	if ((unsigned char)ptr[EI_DATA] == ELFDATA2LSB)
		prints("Little endian\n");
	else if ((unsigned char)ptr[EI_DATA] == ELFDATA2MSB)
		prints("Big endian\n");
	if ((unsigned char)ptr[EI_OSABI] == ELFOSABI_SYSV)
		prints("UNIX system V ABI\n");
	return (EXIT_SUCCESS);
}
