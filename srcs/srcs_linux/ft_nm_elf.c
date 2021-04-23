/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_elf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:33:02 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/23 17:42:34 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			nm_elf(char *ptr, char *offset, char *bin, int opt) {
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	if ((unsigned char)ptr[EI_MAG0] == 0x7f &&
			(unsigned char)ptr[EI_MAG1] == 'E' &&
			(unsigned char)ptr[EI_MAG2] == 'L' &&
			(unsigned char)ptr[EI_MAG3] == 'F') {
		if ((unsigned char)ptr[EI_CLASS] == ELFCLASS64)
			if (elf64(ptr, offset, opt))
				return (EXIT_FAILURE);
	}
	else
		return (ft_perror("Invalid ELF file\n", 0));
	return (EXIT_SUCCESS);

}

int			main(int ac, char **av) {
	int			i, fd, opt = 0;
	char		*ptr;
	struct stat	buff;

	if (ac < 2)
		return (ft_perror("USAGE: ./ft_nm [option] <input files>\n Option:\n  -D,          Display dynamic symbols instead of normal symbols\n", 0));
	if (!strcmp(av[1], "-D"))
		opt = 1;
	i = opt ? 1 : 0;
	while (++i < ac) {
		if ((ac > 2 && i == 1))
			write(1, "\n", 1);
		if (ac > 2) {
			if (opt && ac != 3) {
				prints(av[i]);
				write(1, ":\n", 2);
			}
		}
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
