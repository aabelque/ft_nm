/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/05 17:17:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		handle_64(t_env **e)
{
	int		ncmds;
	int		i;

	i = 0;
	(*e)->header_64 = (struct mach_header_64 *)(*e)->p;
	ncmds = (*e)->header_64->ncmds;
	(*e)->lc = (void *)(*e)->p + sizeof(*(*e)->header_64);
	while (i++ < ncmds)
	{
		if ((*e)->lc->cmd == LC_SYMTAB)
		{
			prints("ici aussi\n");
			(*e)->sym = (struct symtab_command *)(*e)->lc;
			prints("number of symboles: ");
			ft_putnbr((*e)->sym->nsyms);
			printc('\n');
			break ;
		}
	}
}

static void		nm(t_env **e)
{
	int		magic_nb;
	struct mach_header_64	*header;

	magic_nb = *(int *)(*e)->p;
	if (magic_nb == MH_MAGIC_64)
	{
		header = (struct mach_header_64 *)(*e)->p;
		ft_putnbr(header->ncmds);
		handle_64(e);
	}
}

int				main(int ac, char **av)
{
	t_env	*e;

	init_env(&e);
	if (ac != 2)
		return (ft_perror("Usage: ./ft_nm [./binary]\n", e));
	if (open_binary(&e, av[1]))
		return (EXIT_FAILURE);
	nm(&e);
	if (close_binary(&e))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
