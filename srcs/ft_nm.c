/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/15 13:30:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int		nm(char *ptr, off_t offset)
{
	int		magic_nb;

	init_sections();
	magic_nb = *(int *)ptr;
	if (magic_nb == MAGIC_64)
		if (!handle_64(ptr))
			return (EXIT_FAILURE);
	if (magic_nb == MAGIC_32)
		if (!handle_32(ptr))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	int		fd;
	off_t	offset;
	void	*ptr;
	struct stat buff;

	if (ac != 2)
		return (ft_perror("USAGE: ./ft_nm <input files>\n", 0));
	if (open_binary(av[1], &fd, &ptr, &buff))
		return (EXIT_FAILURE);
	offset = buff.st_size;
	nm(ptr, offset);
	if (close_binary(&ptr, &fd, &buff))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
