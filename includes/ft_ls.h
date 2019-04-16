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

typedef	struct dirent	t_dir;
typedef	struct stat	t_stat;
typedef	struct passwd	t_passwd;
typedef	struct group	t_group;

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
	short	flag;
	char	*name;
	t_infols *st;
}		t_ls;

/*
**	right_file
*/
void	sort_ls(t_ls *data, t_lsop **op);
void	file_right(t_stat filestat);
void	file_link(t_stat filestat);
void	file_group(t_stat filestat);
void	file_size(t_stat filestat);
void	file_date(t_stat filestat);

void	ft_lserror(t_ls *st, char *name);
void	free_ftls(t_ls *st);


void	read_dir(t_ls *data, char *base, char *path);
int	read_file(t_ls *data, t_lsop *op, char *base, char *path);

void	ftls_error(t_ls *data);

#endif
