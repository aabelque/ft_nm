/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:40:00 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/14 21:58:05 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <string.h> 

char		*ft_strcpy(char *dest, const char *src)
{
	char	*tmp;

	tmp = dest;
	while ((*dest++ = *src++))
		;
	return (tmp);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void		hexdump(uint64_t n)
{
	int			i, j;   
	int			digit;
	static char	hex[15];

	j = 15;
	for (i = 0; i < 16; i++)
	{
		digit = n & 0xf;
		if (digit >= 10)
			digit += 'a' - 10;
		else
			digit += '0';
		hex[j--] = digit;
		n >>= 4;
	}
	hex[j] = 0;
	prints(hex);
}

void		printc(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int nb)
{
	if (nb < -2147483647)
		prints("-2147483648");
	else
	{
		if (nb < 0)
		{
			printc('-');
			nb = -nb;
		}
		if (nb < 10)
			printc(nb + '0');
		else
		{
			ft_putnbr(nb / 10);
			ft_putnbr(nb % 10);
		}
	}
}

size_t			ft_strlen(const char *s)
{
	const char	*i;

	i = s;
	while (*i)
		i++;
	return (i - s);
}

void		prints(char const *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}
