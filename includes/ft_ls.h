#ifndef FT_LS
# define FT_LS

#include "../libft/includes/libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
//#include <attr/xattr.h>
#include <time.h>
#include <stdio.h>

#define MAJOR(dev) ((int)(((unsigned int) (dev) >> 8) & 0xff))
#define MINOR(dev) ((int)((dev) & 0xff))


# define	LS_L	0
# define	LS_R_MAJ	1
# define	LS_A	2
# define	LS_R	3
# define	LS_T	4
# define	LS_U	5

# define	LS_F	6
# define	LS_G	7
# define	LS_D	8
# define	LS_G_MAJ	9
# define	LS_1	10
# define	LS_F_MAJ	11
# define	LS_C	12
# define	LS_N	13
# define	LS_M	14
# define	LS_P	15
# define	LS_A_MAJ	16

# define	LS_B_MAJ	17
# define	LS_S_MAJ	18
# define	LS_T_MAJ	19


typedef	struct dirent	t_dir;
typedef	struct stat	t_stat;
typedef	struct passwd	t_passwd;
typedef	struct group	t_group;

typedef	struct	s_page
{
	int	link;
	int	group;
	int	group2;
	int	group_i;
	int	group2_i;
	int	size;
	int	size2;
	int	name;
}		t_page;

typedef	struct	s_lsop
{
	char	*name;
	t_stat	file;
	t_dir	*dir;
	struct	s_lsop *next;
}		t_lsop;

typedef	struct	s_infols
{
	int	total;
	char	*path;
	t_lsop	*op;
	struct	s_infols *next;
}		t_infols;

typedef	struct	s_ls
{
	t_bool	error;
	long	flag;
	char	*name;
	int		i;
	int		argc;
	char	indi;
	t_infols *st;
}		t_ls;

/*
**	right_file
*/
void	sort_ls(t_ls *data, t_lsop **mem);
void	file_right(t_ls *data, t_stat filestat, t_page *pad);
void	file_link(t_ls *data, t_stat filestat, t_page *pad);
void	file_group(t_ls *data, t_stat filestat, t_page *pad);
void	file_size(t_ls *data, t_stat filestat, t_page *pad);
void	file_date(t_ls *data, t_stat filestat, t_page *pad);

/*
**	read-file && dir
*/
void	read_dir(t_ls *data, char *base, char *path);
int		read_file(t_ls *data, t_lsop *op, t_page *pad);

/*
**	sort_ls
*/
void	ls_sort_alpha(t_ls *data, t_lsop **op);
void	ls_sort(t_ls *data, t_lsop **op);

/*
**	tools.c
*/
int		ls_putflags(t_ls *data, int argc, char **argv);
void	set_bit(long *st, int i);
void	clear_bit(long *st, int i);
t_bool	test_bit(long *st, int i);
void	ft_lserror(t_ls *st, char *name);
void	ftls_error(t_ls *data);
void	free_ftls(t_ls *st);


#endif
