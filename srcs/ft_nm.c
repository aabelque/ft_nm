/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/04 19:57:33 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		nm(char *p)
{
	prints("c'est cool\n");
}

int			main(int ac, char **av)
{
	t_env	*e;

	init_env(&e);
	if (ac != 2)
	{
		prints("Usage: ./ft_nm [arg]\n");
		free(e);
		return (EXIT_FAILURE);
	}
	if ((e->fd = open(av[1], O_RDONLY)) < 0)
	{
		prints("Can not open fd\n");
		free(e);
		return(EXIT_FAILURE);
	}
	if (fstat(e->fd, &e->buf) < 0)
	{
		prints("fstat error\n");
		close(e->fd);
		free(e);
		return(EXIT_FAILURE);
	}
	if ((e->p = (char *)mmap(0, e->buf.st_size, PROT_READ, MAP_PRIVATE, e->fd, 0)) == MAP_FAILED)
	{
		prints("fstat error\n");
		close(e->fd);
		free(e);
		return(EXIT_FAILURE);
	}
	nm(e->p);
	close(e->fd);
	free(e);
	return (EXIT_SUCCESS);
}
