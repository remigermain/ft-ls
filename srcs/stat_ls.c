/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file_right.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/15 01:46:18 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		sticky_byte(t_stat stat, char right[10])
{
	if (stat.st_mode & S_ISUID)
		right[3] = (stat.st_mode & S_IXUSR) ? 's' : 'S';
	if (stat.st_mode & S_ISGID)
		right[6] = (stat.st_mode & S_IXGRP) ? 's' : 'S';
	if (stat.st_mode & S_ISVTX)
		right[9] = 't';
	else
		right[9] = (stat.st_mode & S_IXOTH) ? 'x' : '-';
}

static void	file_right(t_stat stat, char right[10])
{
	right[0] = '-';
	if (S_ISDIR(stat.st_mode))
		right[0] = 'd';
	else if (S_ISCHR(stat.st_mode))
		right[0] = 'c';
	else if (S_ISBLK(stat.st_mode))
		right[0] = 'b';
	else if (S_ISFIFO(stat.st_mode))
		right[0] = 'p';
	else if (S_ISLNK(stat.st_mode))
		right[0] = 'l';
	else if (S_ISSOCK(stat.st_mode))
		right[0] = 's';
	right[1] = (stat.st_mode & S_IRUSR) ? 'r' : '-';
	right[2] = (stat.st_mode & S_IWUSR) ? 'w' : '-';
	right[3] = (stat.st_mode & S_IXUSR) ? 'x' : '-';
	right[4] = (stat.st_mode & S_IRGRP) ? 'r' : '-';
	right[5] = (stat.st_mode & S_IWGRP) ? 'w' : '-';
	right[6] = (stat.st_mode & S_IXGRP) ? 'x' : '-';
	right[7] = (stat.st_mode & S_IROTH) ? 'r' : '-';
	right[8] = (stat.st_mode & S_IWOTH) ? 'w' : '-';
	sticky_byte(stat, right);
}

static void	file_group(t_ls *data, t_lsop *op, t_pad *pad)
{
	t_passwd	*uid;
	t_group		*gid;

	if (!test_bit(&(data->flag), LS_G))
	{
		if ((uid = getpwuid(op->file.st_uid)) &&
				!test_bit(&(data->flag), LS_N))
			ft_stprintf(KEEP_PF, " %-*s ", pad->group, uid->pw_name);
		else
			ft_stprintf(KEEP_PF, " %-*d ", pad->group, op->file.st_uid);
	}
	if ((gid = getgrgid(op->file.st_gid)) &&
			!test_bit(&(data->flag), LS_N))
		ft_stprintf(KEEP_PF, " %-*s ", pad->group2, gid->gr_name);
	else
		ft_stprintf(KEEP_PF, " %-*d ", pad->group2, op->file.st_gid);
}

static void	file_date(t_ls *data, t_lsop *op)
{
	char	*t;
	long	j;
	int		i;

	i = 5;
	if (test_bit(&(data->flag), LS_U))
		j = op->file.st_atime;
	else if (test_bit(&(data->flag), LS_U_MAJ))
		j = op->file.st_ctime;
	else
		j = op->file.st_mtime;
	t = ctime(&j);
	if (!test_bit(&(data->flag), LS_T_MAJ))
	{
		i = 13;
		if ((data->time + MONTH_SIX) < j || (data->time - MONTH_SIX) > j)
			i = 18;
	}
	ft_stprintf(KEEP_PF, " %.*s ", ft_strlen(t) - i, t + 4);
	if (i == 18)
		ft_stprintf(KEEP_PF, "%.*s ", 4, t + 20);
}

void		file_info(t_ls *data, t_lsop *op, t_pad *pad, char *path)
{
	char	right[10];

	file_right(op->file, right);
	ft_stprintf(KEEP_PF, "%.10s", right);
	file_acl(data, op, path);
	ft_stprintf(KEEP_PF, " %*d", pad->link, op->file.st_nlink);
	file_group(data, op, pad);
	if (S_ISBLK(op->file.st_mode) || S_ISCHR(op->file.st_mode))
		ft_stprintf(KEEP_PF, " %3lld, %3lld",
				major(op->file.st_rdev),
				minor(op->file.st_rdev));
	else
		ft_stprintf(KEEP_PF, " %*llu", (pad->mm ? 8 : pad->size),
				op->file.st_size);
	file_date(data, op);
}
