/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:43:06 by aabelque          #+#    #+#             */
/*   Updated: 2021/05/05 15:08:37 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			check_endianess(int	e_ident) {

	switch (e_ident) {
		case ELFDATA2LSB:
			endianess = LITTLE;
		case ELFDATA2MSB:
			endianess = BIG;
		default:
			return (ft_perror("Corrupted file\n", 0));
	}
}

int			check_offset_elf(char *ptr, char  *offset) {
	if (ptr > offset)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void		ft_qsort_symelf(t_elf_symbol *sym, int left, int right, int (*comp)(const char *, const char *)) {
	int			last, i, r;

	if (left >= right)
		return ;
	ft_swap_symelf(sym, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		r = comp(sym[i].name, sym[left].name);
		if (r < 0 || (r == 0 && sym[i].value < sym[left].value))
			ft_swap_symelf(sym, ++last, i);
	}
	ft_swap_symelf(sym, left, last);
	ft_qsort_symelf(sym, left, last - 1, comp);
	ft_qsort_symelf(sym, last + 1, right, comp);
}

/* static int	partition(t_elf_symbol *sym, int low, int high, int (*comp)(const char *, const char *)) { */
/* 	int				idx, r; */
/* 	t_elf_symbol	pivot; */

/* 	pivot = sym[high]; */
/* 	idx = low - 1; */
/* 	for (int j = low; j <= high; j++) { */
/* 		r = comp(sym[j].name, pivot.name); */
/* 		if (r < 0) { */
/* 			idx++; */
/* 			ft_swap_symelf(sym, idx, j); */
/* 		} */
/* 		else if (r == 0 && sym[j].value < pivot.value) { */
/* 			prints(sym[j].name); */
/* 			prints(" - "); */
/* 			prints(pivot.name); */
/* 			printc('\n'); */
/* 			idx++; */
/* 			ft_swap_symelf(sym, idx, j); */
/* 		} */
/* 	} */
/* 	ft_swap_symelf(sym, idx + 1, high); */
/* 	return (idx + 1); */
/* } */

/* void		ft_qsort_symelf(t_elf_symbol *sym, int low, int high, int (*comp)(const char *, const char *)) { */
/* 	int		pidx; */

/* 	if (low < high) { */
/* 		pidx = partition(sym, low, high, comp); */
/* 		ft_qsort_symelf(sym, low, pidx - 1, comp); */
/* 		ft_qsort_symelf(sym, pidx + 1, high, comp); */
/* 	} */
/* } */

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
