/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/23 12:24:48 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>
#include <string.h> 

# define ERROR(s) prints(s) 
# define RD PROT_READ
# define PRIV MAP_PRIVATE

# if __APPLE__
	#include <mach-o/loader.h>
	#include <mach-o/fat.h>
	#include <mach-o/nlist.h>
	#include <ar.h>
	# define AR_MAGIC 0x72613c21
	# define AR_CIGAM 0x213c6172
	# define MAGIC_64 MH_MAGIC_64
	# define CIGAM_64 MH_CIGAM_64
	# define MAGIC_32 MH_MAGIC
	# define CIGAM_32 MH_CIGAM
	# define FAT FAT_MAGIC
	# define TAF FAT_CIGAM
	# define FAT64 FAT_MAGIC_64
	# define TAF64 FAT_CIGAM_64
	# define SYMTAB LC_SYMTAB
	# define SEGMENT64 LC_SEGMENT_64
	# define SEGMENT32 LC_SEGMENT
# elif __linux__
	#include </usr/include/elf.h>
	#include </usr/include/bsd/nlist.h>
	# define MAX_SECTIONS 34
# else
	ERROR("It only work on MAC OS and LINUX system\n")
# endif

typedef struct	s_elf_section
{
	char			*name;
}				t_elf_section;

typedef struct	s_elf_symbol
{
	char			*name;
	uint8_t			type;
	uint8_t			bind;
	uint8_t			shndx;
	uint64_t		value;
}				t_elf_symbol;

typedef struct	s_symbol
{
	char			*name;
	uint8_t			n_type;
	uint8_t			n_sect;
	uint8_t			ext;
	uint64_t		n_value;
}				t_symbol;

typedef struct	s_section
{
	uint32_t	index;
	uint32_t	text;
	uint32_t	data;
	uint32_t	bss;
}				t_section;

/* ******************** ELF files ******************** */
int						open_binary_elf(char *bin, int *fd, char **ptr, struct stat *buff);
int						close_binary_elf(char **ptr, int *fd, struct stat *buff);
int						nm_elf(char *ptr, char *offset, char *bin);
int						check_offset_elf(char *ptr, char *offset);
int						elf64(char *ptr, char *offset);
Elf64_Shdr				*get_shdr(Elf64_Ehdr *eh);
char					*get_strtable(Elf64_Ehdr *eh);
char					*get_strname(Elf64_Ehdr *eh, int offset);
void					ft_swap_symelf(t_elf_symbol *sym, int i, int j);
void					ft_qsort_symelf(t_elf_symbol *sym, int left, int right, int (*comp)(const char *, const char *));
long long				swap_bytes(long long x);


/* ******************** Mach-o file ******************** */

int						handle_64(void *ptr, void *offset);
int						handle_32(void *ptr, void *offset);
int						fat32(void *ptr, void *offset, char *bin);
int						fat64(void *ptr, void *offset, char *bin);
int						ar(void *ptr, void *offset, char *bin);
int						close_binary(void **ptr, int *fd, struct stat *buff);
int						open_binary(char *bin, int *fd, void **ptr, struct stat *buff);
int						nm(void *ptr, void *offset, char *bin);
int						check_offset(void *ptr, void *offset);
void					ft_swap_symbol(t_symbol *sym, int i, int j);
void					ft_qsort_symbol(t_symbol *sym, int left, int right, int (*comp)(const char *, const char *));
struct load_command		*swaplc_32(struct load_command *lc);
struct symtab_command	*swapsym_32(struct symtab_command *sym);
struct nlist			swapnlst_32(struct nlist nlst);
void					init_sections(void);
t_section				*sections(void);

/* ******************** SHARED FUNCTIONS ******************** */

int						ft_perror(char *s, int fd);
uint32_t				swap32(uint32_t x);
uint32_t				ppc32(uint32_t x);
uint64_t				ppc64(uint64_t x);
uint64_t				swap64(uint64_t x);
void					set_ppc(uint8_t ppc);

/* ******************** LIB C ******************** */

int						ft_strcmp(const char *s1, const char *s2);
int						ft_atoi(const char *str);
size_t					ft_strlen(const char *s);
void					prints(char const *s);
void					printc(char c);
void					ft_putnbr(int nb);
void					hexdump(uintmax_t addr, size_t base, size_t len);
char					*ft_strdup(const char *s);

