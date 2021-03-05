/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:43:06 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/05 19:15:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			close_binary(t_env **e)
{
	if (munmap((*e)->p, (*e)->buf.st_size))
		return (ft_perror("Can't munmap ptr\n", *e));
	close((*e)->fd);
	free(*e);
	return (EXIT_SUCCESS);
}

int			open_binary(t_env **e, char *bin)
{
	if (((*e)->fd = open(bin, O_RDONLY)) < 0)
		return (ft_perror("Can not open fd\n", *e));
	if (fstat((*e)->fd, &(*e)->buf) < 0)
		return (ft_perror("fstat error\n", *e));
	if (((*e)->p = (char *)mmap(0, (*e)->buf.st_size,
					RD, PRIV, (*e)->fd, 0)) == MAP_FAILED)
		return (ft_perror("fstat error\n", *e));
	return (EXIT_SUCCESS);
}

int			ft_perror(char *s, t_env *e)
{
	prints(s);
	if (e->fd)
		close(e->fd);
	free(e);
	return (EXIT_FAILURE);
}

void		init_env(t_env	**e)
{
	*e = (t_env *)malloc(sizeof(t_env));
	(*e)->fd = 0;
	(*e)->p = NULL;
	(*e)->header_64 = NULL;
	(*e)->header_32 = NULL;
	(*e)->lc = NULL;
	(*e)->sym = NULL;
}
