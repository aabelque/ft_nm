/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_elf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:33:02 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/02 15:59:04 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			nm_elf(char *ptr, char *offset, char *bin)
{
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	if ((unsigned char)ptr[EI_MAG0] == 0x7f &&
			(unsigned char)ptr[EI_MAG1] == 'E' &&
			(unsigned char)ptr[EI_MAG2] == 'L' &&
			(unsigned char)ptr[EI_MAG3] == 'F')
	{
		prints("It's an elf file\n");
	}
	return (EXIT_SUCCESS);

}

int			main(int ac, char **av)
{
	int			i, fd;
	char		*ptr;
	struct stat	buff;

	i = 0;
	if (ac < 2)
		return (ft_perror("USAGE: ./ft_nm <input files>\n", 0));
	while (++i < ac)
	{
		if (ac > 2 && i == 1)
			write(1, "\n", 1);
		if (ac > 2)
		{
			prints(av[i]);
			write(1, ":\n", 2);
		}
		if (open_binary_elf(av[1], &fd, &ptr, &buff))
			return (EXIT_FAILURE);
		nm_elf(ptr, ptr + buff.st_size, av[1]);
		if (close_binary_elf(&ptr, &fd, &buff))
			return (EXIT_FAILURE);
		if (ac > 2 && (i + 1) != ac)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
