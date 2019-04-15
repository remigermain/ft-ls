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

typedef	struct dirent	t_dir;
typedef	struct stat	t_stat;
typedef	struct passwd	t_passwd;

typedef	struct	s_ls
{
	void	*dir_ptr;
	short	flag;

	t_dir	*dir;
	t_stat	stat;

}		t_ls;


/*
**	right_file
*/
void	file_right(t_stat filestat);
void	file_link(t_stat filestat);
void	file_group(t_stat filestat);
void	file_size(t_stat filestat);
void	file_date(t_stat filestat);

void	ft_lserror(t_ls *st, char *name);

#endif
