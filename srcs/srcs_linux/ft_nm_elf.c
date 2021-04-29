/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_elf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:33:02 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/29 14:43:54 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				nm_elf(char *ptr, char *offset, char *bin, int opt) {
	struct ar_hdr	*ar;

	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	if ((unsigned char)ptr[EI_MAG0] == 0x7f &&
			(unsigned char)ptr[EI_MAG1] == 'E' &&
			(unsigned char)ptr[EI_MAG2] == 'L' &&
			(unsigned char)ptr[EI_MAG3] == 'F') {
		write(1, "X", 1);
		if ((unsigned char)ptr[EI_CLASS] == ELFCLASS64)
			if (elf64(ptr, offset, opt))
				return (EXIT_FAILURE);
		if ((unsigned char)ptr[EI_CLASS] == ELFCLASS32)
			if (elf32(ptr, offset, opt))
				return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG)) {
		struct ar_hdr *ar = (struct ar_hdr *)ptr;
		prints(ar[1].ar_name);
		prints(ar[1].ar_date);
		prints(ar[1].ar_uid);
		prints(ar[1].ar_gid);
		prints(ar[1].ar_mode);
		prints(ar[1].ar_size);
	}
	else
		return (ft_perror("Invalid ELF file\n", 0));
	return (EXIT_SUCCESS);

}

static int		get_option(int ac, char *arg, int *option) {
	if (!strcmp(arg, "-D"))
		*option = 1;
	if (*option && ac > 3)
		write(1, "\n", 1);
	return (*option);
}

static void		output_formatted(int ac, int idx, int opt, char *arg) {
	if (ac > 2 && (idx == 1))
		write(1, "\n", 1);
	if (ac > 2) {
		if ((opt && ac != 3) || (!opt)) {
			prints(arg);
			write(1, ":\n", 2);
		}
	}
}

int				main(int ac, char **av) {
	int			i, fd, opt = 0;
	char		*ptr;
	struct stat	buff;

	if (ac < 2)
		return (ft_perror("USAGE: ./ft_nm [option] <input files>\n Option:\n  -D,          Display dynamic symbols instead of normal symbols\n", 0));
	i = get_option(ac, av[1], &opt);
	while (++i < ac) {
		output_formatted(ac, i, opt, av[i]);
		if (open_binary_elf(av[i], &fd, &ptr, &buff))
			return (EXIT_FAILURE);
		nm_elf(ptr, ptr + buff.st_size, av[i], opt);
		if (close_binary_elf(&ptr, &fd, &buff))
			return (EXIT_FAILURE);
		if (ac > 2 && (i + 1) != ac)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
