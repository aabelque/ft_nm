/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/30 16:24:13 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		nm(void *ptr, void  *offset, char *bin)
{
	int					magic_nb;

	init_sections();
	if (check_offset(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	magic_nb = *(int *)ptr;
	switch (magic_nb)
	{
		case CIGAM_32:
		case MAGIC_32:
			if (handle_32(ptr, offset))
					return (EXIT_FAILURE);
			break;
		case CIGAM_64:
		case MAGIC_64:
			if (handle_64(ptr, offset))
				return (EXIT_FAILURE);
			break;
		case TAF64:
		case FAT64:
			if (fat64(ptr, offset, bin))
				return (EXIT_FAILURE);
			break;
		case TAF:
		case FAT:
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

int				main(int ac, char **av)
{
	int		fd;
	void	*ptr;
	struct stat buff;

	if (ac != 2)
		return (ft_perror("USAGE: ./ft_nm <input files>\n", 0));
	if (open_binary(av[1], &fd, &ptr, &buff))
		return (EXIT_FAILURE);
	nm(ptr, ptr + buff.st_size, av[1]);
	if (close_binary(&ptr, &fd, &buff))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
