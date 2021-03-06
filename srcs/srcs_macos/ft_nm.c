/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/23 19:35:19 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			nm(void *ptr, void  *offset, char *bin)
{
	int			magic_nb;

	init_sections();
	if (check_offset(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	magic_nb = *(int *)ptr;
	switch (magic_nb)
	{
		case MH_CIGAM:
		case MH_MAGIC:
			if (handle_32(ptr, offset))
					return (EXIT_FAILURE);
			break;
		case MH_CIGAM_64:
		case MH_MAGIC_64:
			if (handle_64(ptr, offset))
				return (EXIT_FAILURE);
			break;
		case FAT_CIGAM_64:
		case FAT_MAGIC_64:
			if (fat64(ptr, offset, bin))
				return (EXIT_FAILURE);
			break;
		case FAT_CIGAM:
		case FAT_MAGIC:
			if (fat32(ptr, offset, bin))
				return (EXIT_FAILURE);
			break;
		case AR_MAGIC:
		case AR_CIGAM:
			if (ar(ptr, offset, bin))
				return (EXIT_FAILURE);
			break;
		default:
			return (ft_perror("No magic number\n", 0));
	}
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	int			i, fd;
	void		*ptr;
	struct stat buff;

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
		if (open_binary(av[i], &fd, &ptr, &buff))
			return (EXIT_FAILURE);
		nm(ptr, ptr + buff.st_size, av[i]);
		if (close_binary(&ptr, &fd, &buff))
			return (EXIT_FAILURE);
		if (ac > 2 && (i + 1) != ac)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
