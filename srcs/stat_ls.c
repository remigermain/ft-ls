/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file_right.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 23:30:23 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	file_acl(t_ls *data, t_lsop *op, t_padding *pad)
{
	if (test_bit(&(data->flag), LS_L))
	{
		if (op->xattr > 0)
			ft_printf("@");
		else if (data->path &&
				getxattr(data->path, op->name, NULL, 0, 0, XATTR_NOFOLLOW) >= 0)
			ft_printf("+");
		else
			ft_printf(" ");
	}
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
	if (stat.st_mode & S_ISVTX)
		right[9] = 't';
	else
		right[9] = (stat.st_mode & S_IXOTH) ? 'x' : '-';
}

static void	file_group(t_ls *data, t_lsop *op, t_padding *pad)
{
	t_passwd	*uid;
	t_group		*gid;

	if (!test_bit(&(data->flag), LS_G))
	{
		if ((uid = getpwuid(op->file.st_uid)) &&
				!test_bit(&(data->flag), LS_N))
			ft_printf(" %-*s ", pad->group, uid->pw_name);
		else
			ft_printf(" %-*d ", pad->group, op->file.st_uid);
	}
	if ((gid = getgrgid(op->file.st_gid)) &&
			!test_bit(&(data->flag), LS_N))
		ft_printf(" %-*s", pad->group2, gid->gr_name);
	else
		ft_printf(" %-*d", pad->group2, op->file.st_gid);
}

void		file_info(t_ls *data, t_lsop *op, t_padding *pad)
{
	char	right[10];
	char	*time;
	int		i;

	i = 13;
	file_right(op->file, right);
	ft_printf("%.10s", right);
	file_acl(data, op, pad);
	ft_printf(" %*d", pad->link, op->file.st_nlink);
	file_group(data, op, pad);
	if (S_ISBLK(op->file.st_mode) || S_ISCHR(op->file.st_mode))
		ft_printf(" %*lld, %*lld", pad->size, MAJOR(op->file.st_rdev),
				pad->size2, MINOR(op->file.st_rdev));
	else
		ft_printf("%*d", pad->size + pad->size2 + 2, op->file.st_size);
	if (test_bit(&(data->flag), LS_U))
		time = ctime(&(op->file.st_atime));
	else
		time = ctime(&(op->file.st_ctime));
	if (test_bit(&(data->flag), LS_T_MAJ))
		i = 5;
	ft_printf(" %.*s ", ft_strlen(time) - i, time + 4);
}
