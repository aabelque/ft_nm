/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:40:00 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/05 09:40:18 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		printc(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int nb)
{
	if (nb == INT_MAX)
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
