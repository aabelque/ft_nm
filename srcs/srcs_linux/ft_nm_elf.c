/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_elf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:33:02 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/02 14:55:44 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			nm(void *ptr, void *offset, char *bin)
{
	if (check_offset(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	if (ft_strcmp((unsigned char)ptr[ELFMAG], "\177ELF"))
		prints("It's an elf file\n");
	return (EXIT_SUCCESS);

}

int			main(int ac, char **av)
{
	int			i, fd;
	void		*ptr;
	struct stat	buff;

	i = 1;
	if (ac < 2)
		return (ft_perror("USAGE: ./ft_nm <input files>\n", 0));
	while (++i < ac)
	{
		if (ac > 2 && i == 1)
			write(1, "\n", 1);
		if (ac > 2)
		{
			prints(av[i]);
			write(1, ":\n", 2);
		}
		if (open_binary(av[1], &fd, &ptr, &buff))
			return (EXIT_FAILURE);
		nm(ptr, ptr + buff.st_size, av[1]);
		if (close_binary(&ptr, &fd, &buff))
			return (EXIT_FAILURE);
		if (ac > 2 && (i + 1) != ac)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
