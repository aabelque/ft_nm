/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/05 09:29:20 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define ERROR(s) prints(s) 

#if __APPLE__
	#include <mach-o/loader.h>
	#include <mach-o/nlist.h>
#elif __linux__
	#include </usr/include/linux/elf.h>
	#include </usr/include/bsd/nlist.h>
#else
	ERROR("I only work on MAC OS or LINUX system\n")
#endif

typedef struct	s_env
{
	int32_t		fd;
	char		*p;
	struct stat	buf; 

}				t_env;


int			ft_strlen(char *s);
void		prints(char *s);
void		printc(char c);
void		ft_putnbr(int nb);
void		init_env(t_env **e);
/* void		nm(); */
