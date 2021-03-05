/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:43:06 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/04 19:56:48 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		printc(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int nb)
{
	if (nb == INT32_MAX)
		prints("-2147483648");
	else
	{
		if (nb < 0)
		{
			printc('-');
			nb = -nb;
		}
		if (nb <= 9)
			printc(nb + '0');
		else
		{
			ft_putnbr(nb / 10);
			ft_putnbr(nb % 10);
		}
	}
}

int			ft_strlen(char *s)
{
	char	*i;

	i = s;
	while (*i)
		i++;
	return (i - s);
}

void		prints(char *s)
{
	write(1, s, ft_strlen(s));
}

void		init_env(t_env	**e)
{
	*e = (t_env *)malloc(sizeof(t_env));
	(*e)->fd = 0;
	(*e)->p = NULL;
}
