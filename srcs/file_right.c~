#include "ft_ls.h"


void	file_right(t_stat fileStat)
{
	char	right[10];

	if (S_ISDIR(fileStat.st_mode))
		right[0] = 'd';
	else if (S_ISCHR(fileStat.st_mode))
		right[0] = 'c';
	else if (S_ISBLK(fileStat.st_mode))
		right[0] = 'b';
	else if (S_ISFIFO(fileStat.st_mode))
		right[0] = 'p';
	else if (S_ISLNK(fileStat.st_mode))
		right[0] = 'l';
	else if (S_ISSOCK(fileStat.st_mode))
		right[0] = 's';
	else
		right[0] = '-';
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
	t_group		*gid;

	if ((uid = getpwuid(filestat.st_uid)))
		ft_printf("%s ", uid->pw_name);
	else
		ft_printf("%-8d ", filestat.st_uid);
	if ((gid = getgrgid(filestat.st_gid)))
		ft_printf("%s ", gid->gr_name);
	else
		ft_printf("%-8d ", filestat.st_gid);
}

void	file_size(t_stat filestat)
{
	if (S_ISBLK(filestat.st_mode) || S_ISCHR(filestat.st_mode))
		ft_printf(" %lld, %lld ", MAJOR(filestat.st_rdev), MINOR(filestat.st_rdev));
	else
		ft_printf(" %d ", filestat.st_size);
}

void	file_date(t_stat filestat)
{
	char	*time;

	time = ctime(&(filestat.st_ctime));
	ft_printf(" %.*s ", ft_strlen(time) - 1, time);
}
