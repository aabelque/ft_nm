/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:43:06 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/31 20:33:02 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			check_offset(void *ptr, void  *offset)
{
	if (ptr > offset)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void		ft_qsort_symbol(t_symbol *sym, int left, int right, int (*comp)(const char *, const char *))
{
	int			last, i, r;

	if (left >= right)
		return ;
	ft_swap_symbol(sym, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
	{
		r = comp(sym[i].name, sym[left].name);
		if (r < 0 || (r == 0 && sym[i].n_value < sym[left].n_value))
			ft_swap_symbol(sym, ++last, i);
	}
	ft_swap_symbol(sym, left, last);
	ft_qsort_symbol(sym, left, last - 1, comp);
	ft_qsort_symbol(sym, last + 1, right, comp);
}

void		ft_swap_symbol(t_symbol *sym, int i, int j)
{
	t_symbol	tmp;

	tmp = sym[i];
	sym[i] = sym[j];
	sym[j] = tmp;
}

int			close_binary(void **ptr, int *fd, struct stat *buff)
{
	if (munmap(*ptr, buff->st_size))
		return (ft_perror("Can't munmap ptr\n", *fd));
	close(*fd);
	return (EXIT_SUCCESS);
}

int			open_binary(char *bin, int *fd, void **ptr, struct stat *buff)
{
	if ((*fd = open(bin, O_RDONLY)) < 0)
	{
		if (*fd == -1 && errno == EACCES)
			return (ft_perror("Permission denied.\n", *fd));
		else if (*fd == -1)
			return (ft_perror("No such file or directory.\n", *fd));
	}
	if (fstat(*fd, buff) < 0)
		return (ft_perror("Not a valid open file descriptor.\n", *fd));
	if (S_ISDIR(buff->st_mode))
		return (ft_perror("Is a directory.\n", *fd));
	if ((*ptr = mmap(0, buff->st_size, RD, PRIV, *fd, 0)) == MAP_FAILED)
		return (ft_perror("Can't mmap\n", *fd));
	return (EXIT_SUCCESS);
}

int			ft_perror(char *s, int fd)
{
	write(2, s, ft_strlen(s));
	if (fd)
		close(fd);
	return (EXIT_FAILURE);
}

t_section	*sections(void)
{
	static t_section	sections = {0, 0, 0, 0};
	return (&sections);
}

void		init_sections(void)
{
	sections()->index = 0;
	sections()->text = 0;
	sections()->data = 0;
	sections()->bss = 0;
}
