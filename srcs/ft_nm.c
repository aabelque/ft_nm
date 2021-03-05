/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/05 09:56:07 by aabelque         ###   ########.fr       */
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
		return (ft_perror("Usage: ./ft_nm [./binary]\n", e));
	if (open_binary(&e, av[1]))
		return (EXIT_FAILURE);
	nm(e->p);
	close(e->fd);
	free(e);
	return (EXIT_SUCCESS);
}
