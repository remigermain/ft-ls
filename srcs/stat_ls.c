/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file_right.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 09:49:11 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	file_right(t_ls *data, t_stat fileStat, t_padding *pad)
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

void	file_link(t_ls *data, t_stat filestat, t_padding *pad)
{
	ft_printf("  %*d", pad->link, filestat.st_nlink);
}

void	file_group(t_ls *data, t_stat filestat, t_padding *pad)
{
	t_passwd	*uid;
	t_group		*gid;

	if (!test_bit(&(data->flag), 7))
	{
		if ((uid = getpwuid(filestat.st_uid)) &&
				!test_bit(&(data->flag), LS_N))
			ft_printf(" %-*s ", pad->group, uid->pw_name);
		else
			ft_printf(" %-*d ", pad->group_i, filestat.st_uid);
	}
	if ((gid = getgrgid(filestat.st_gid)) &&
			!test_bit(&(data->flag), LS_N))
		ft_printf(" %-*s", pad->group2, gid->gr_name);
	else
		ft_printf(" %-*d", pad->group2_i, filestat.st_gid);
}

void	file_size(t_ls *data, t_stat filestat, t_padding *pad)
{
	if (S_ISBLK(filestat.st_mode) || S_ISCHR(filestat.st_mode))
		ft_printf(" %*lld, %*lld", pad->size, MAJOR(filestat.st_rdev), pad->size2, MINOR(filestat.st_rdev));
	else
		ft_printf("%*d", pad->size + pad->size2 + 2, filestat.st_size);
}

void	file_date(t_ls *data, t_stat filestat, t_padding *pad)
{
	char	*time;
	int		i;

	i = 13;
	if (test_bit(&(data->flag), LS_U))
		time = ctime(&(filestat.st_atime));
	else
		time = ctime(&(filestat.st_ctime));
	if (test_bit(&(data->flag), LS_T_MAJ))
		i = 5;
	ft_printf(" %.*s ", ft_strlen(time) - i, time + 4);
}