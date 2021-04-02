/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:10:01 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/31 20:31:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			main(int ac, char **av)
{
	int			i, fd;
	void		*ptr;
	struct stat	buff;

	i = 1;
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
		if (open_binary(av[1], &fd, &ptr, &buff))
			return (EXIT_FAILURE);
		nm(ptr, ptr + buff.st_size, av[1]);
		if (close_binary(&ptr, &fd, &buff))
			return (EXIT_FAILURE);
		if (ac > 2 && (i + 1) != ac)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
