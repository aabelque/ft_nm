/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:43:06 by aabelque          #+#    #+#             */
/*   Updated: 2021/05/04 17:06:20 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			check_offset_elf(char *ptr, char  *offset) {
	if (ptr > offset)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* void		ft_qsort_symelf(t_elf_symbol *sym, int left, int right, int (*comp)(const char *, const char *)) { */
/* 	int			last, i, r; */

/* 	if (left >= right) */
/* 		return ; */
/* 	ft_swap_symelf(sym, left, (left + right) / 2); */
/* 	last = left; */
/* 	for (i = left + 1; i <= right; i++) { */
/* 		r = comp(sym[i].name, sym[left].name); */
/* 		if (r < 0 || (r == 0 && sym[i].value < sym[left].value)) */
/* 			ft_swap_symelf(sym, ++last, i); */
/* 	} */
/* 	ft_swap_symelf(sym, left, last); */
/* 	ft_qsort_symelf(sym, left, last - 1, comp); */
/* 	ft_qsort_symelf(sym, last + 1, right, comp); */
/* } */

void		ft_qsort_symelf(t_elf_symbol *sym, int nb_element, int (*comp)(const char *, const char *)) {
	int				i, j;
	t_elf_symbol	current;

	if (nb_element < 2)
		return ;
	for (i = 0; i < nb_element; i++) {
		current = sym[i];
		for (j = i; j > 0 && ((comp(sym[j - 1].name, current.name) > 0)
					|| ((comp(sym[j - 1].name, current.name) == 0
							&& sym[j - 1].value > current.value))); j--) {
			sym[j] = sym[j - 1];
		}
		sym[j] = current;
	}
}

static void	merge(t_elf_symbol *sym, int left, int mid, int right, int (*comp)(const char *, const char *)) {
	int i, j, k;
	int sizel = mid - left + 1;
	int	sizer = right - mid;
	t_elf_symbol tabl[sizel], tabr[sizer];

	ft_putnbr(left);
	printc('\n');
	ft_putnbr(mid);
	printc('\n');
	ft_putnbr(right);
	printc('\n');
	for (int i = 0; i < sizel; i++)
		tabl[i] = sym[left + i];
	for (int j = 0; j < sizer; j++)
		tabl[j] = sym[mid + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < sizel && j < sizer) {
		if (comp(tabl[i].name, tabr[j].name) < 0) {
			sym[k] = tabl[i];
			i++;
		}
		else if ((comp(tabl[i].name, tabr[j].name) == 0) 
				&& (tabl[i].value < tabr[j].value)) {
			sym[k] = tabl[i];
			i++;
		}
		else {
			sym[k] = tabr[j];
			j++;
		}
		k++;
	}
	while (i < sizel) {
		sym[k] = tabl[i];
		i++;
		k++;
	}
	while (j < sizer) {
		sym[k] = tabr[j];
		j++;
		k++;
	}
}

void		merge_sort(t_elf_symbol *sym, int left, int right, int (*comp)(const char *, const char *)) {
	int		mid;

	ft_putnbr(left);
	printc('\n');
	ft_putnbr(right);
	printc('\n');
	if (left < right) {
		mid = left + (right - left) / 2;
		merge_sort(sym, left, mid, comp);
		merge_sort(sym, mid + 1, right, comp);
		merge(sym, left, mid, right, comp);
	}
}

void		ft_swap_symelf(t_elf_symbol *sym, int i, int j) {
	t_elf_symbol	tmp;

	tmp = sym[i];
	sym[i] = sym[j];
	sym[j] = tmp;
}

int			close_binary_elf(char **ptr, int *fd, struct stat *buff) {
	if (munmap(*ptr, buff->st_size))
		return (ft_perror("Can't munmap ptr\n", *fd));
	close(*fd);
	return (EXIT_SUCCESS);
}

int			open_binary_elf(char *bin, int *fd, char **ptr, struct stat *buff) {
	if ((*fd = open(bin, O_RDONLY)) < 0) {
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

int			ft_perror(char *s, int fd) {
	write(2, s, ft_strlen(s));
	if (fd)
		close(fd);
	return (EXIT_FAILURE);
}
