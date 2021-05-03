/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:40:00 by aabelque          #+#    #+#             */
/*   Updated: 2021/05/03 13:07:11 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\n'
			|| c == '\v')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int			i, sign;
	long		nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	if (!str[i])
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i++] - '0');
	}
	return (nbr * sign);
}

char	*ft_strndup(const char *s, size_t n)
{
	char *ptr;

	ptr = malloc(sizeof(char *) * n + 1);
	if (!ptr)
		return (NULL);
	while (n--)
	{
		printc('X');
		*ptr++ = *s++;
	}
	*ptr = '\0';
	return (ptr);
}

int				ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		++s1;
		++s2;
	}
	return (0);
}

int				ft_strcmp(const char *s1, const char *s2)
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

void			hexdump(uintmax_t addr, size_t base, size_t len)
{
	char		value;
	char		hex[16] = "0123456789abcdef";

	if (len < 1)
		return ;
	hexdump(addr / base, base, len - 1);
	value = hex[(addr % base)];
	write(1, &value, 1);
}

void			printc(char c)
{
	write(1, &c, 1);
}

void			ft_putnbr(int nb)
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

void			prints(char const *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}
