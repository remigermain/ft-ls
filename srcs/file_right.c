#include "ft_ls.h"


void	file_right(t_stat fileStat)
{
	char	right[10];
	
	right[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
	right[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
	right[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	right[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	right[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	right[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	right[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	right[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	right[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	right[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
	write(1, right, 10);
}

void	file_link(t_stat filestat)
{
	ft_printf(" %d ", filestat.st_nlink);
}

void	file_group(t_stat filestat)
{
	t_passwd	*uid;

	uid = getpwuid(filestat.st_uid);
	ft_printf("%s ", uid->pw_name);
	uid = getpwuid(filestat.st_gid);
	ft_printf("%s ", uid->pw_name);

}

void	file_size(t_stat filestat)
{
	ft_printf(" %d ", filestat.st_size);
}

void	file_date(t_stat filestat)
{
	ft_printf(" time ", ctime(&(filestat.st_ctime)));
}
