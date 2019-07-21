/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/15 02:08:28 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static t_bool	file_acl(t_ls *data, t_lsop *op, char *path)
{
	acl_entry_t dummy;
	acl_t		acl;
	char		*path_total;

	if (test_bit(&(data->flag), LS_L))
	{
        if (!(path_total = cat_path(op->name, path)))
            return (FALSE);
		acl = acl_get_link_np(path_total, ACL_TYPE_EXTENDED);
		if (op->xattr > 0)
			ft_stprintf(KEEP_PF, "@");
		else if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) != -1)
			ft_stprintf(KEEP_PF, "+");
		else
			ft_stprintf(KEEP_PF, " ");
		ft_strdel(&path_total);
		acl_free((void *)acl);
	}
    return (true);
}

void		sticky_byte(t_stat stat, char right[10])
{
	if (stat.st_mode & S_ISVTX)
		right[9] = 't';
	else
		right[9] = (stat.st_mode & S_IXOTH) ? 'x' : '-';
	if (S_ISGID & stat.st_mode)
	{
		right[3] = (stat.st_mode & S_IXUSR) ? 's' : 'S';
		right[6] = (stat.st_mode & S_IXUSR) ? 's' : 'S';
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

	if (test_bit(&(data->flag), LS_U))
		j = op->file.st_atime;
	else if (test_bit(&(data->flag), LS_U_MAJ))
		j = op->file.st_ctime;
	else
		j = op->file.st_mtime;
	i = (test_bit(&(data->flag), LS_T_MAJ) ? 5 : 13);
	t = ctime(&j);
	if ((data->time + MONTH_SIX) < j || (data->time - MONTH_SIX) > j)
		i = 18;
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
		ft_stprintf(KEEP_PF, " %*d", (pad->mm ? 8 : pad->size),
				op->file.st_size);
	file_date(data, op);
}

static t_bool		print_link(t_ls *data, t_lsop *op, t_pad *pad, char *path)
{
	char	buff[1024];
    char    *path_new;
	int		i;
	int    size = 0;

	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_M) &&
			!test_bit(&(data->flag), LS_1) && op->next &&
			(size + pad->name) < data->w.ws_col)
		ft_stprintf(KEEP_PF, " %*@", pad->name - ft_strlen(op->name),
				"char", ' ');
	else if (test_bit(&(data->flag), LS_M))
		ft_stprintf(KEEP_PF, " ");
	if (S_ISLNK(op->file.st_mode) && test_bit(&(data->flag), LS_L))
	{
        if (!(path_new = cat_path(op->name, path)))
            return (FALSE);
		if ((i = readlink(path_new, buff, 1023)) > 0)
			ft_stprintf(KEEP_PF, " -> %.*s", i, buff);
        ft_memdel((void**)&path_new);
	}
	if (test_bit(&(data->flag), LS_L) || test_bit(&(data->flag), LS_1))
		ft_stprintf(KEEP_PF, "\n");
	ft_stprintf(OUT_PF, "");
	return (TRUE);
}

static  void		print_extra(t_ls *data, t_lsop *op)
{
	if (test_bit(&(data->flag), LS_A) || test_bit(&(data->flag), LS_F) || op->name[0] != '.')
		ft_stprintf(KEEP_PF, "%s", op->name);
	if (test_bit(&(data->flag), LS_G_MAJ))
		ft_stprintf(KEEP_PF, "%s", T_WHITE);
	if (test_bit(&(data->flag), LS_F_MAJ))
	{
		if (S_ISDIR(op->file.st_mode))
			ft_stprintf(KEEP_PF, "/");
		else if (S_ISFIFO(op->file.st_mode))
			ft_stprintf(KEEP_PF, "|");
		else if (S_ISLNK(op->file.st_mode))
			ft_stprintf(KEEP_PF, "@");
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP ||
				op->file.st_mode & S_IXOTH)
			ft_stprintf(KEEP_PF, "*");
	}
	else if (test_bit(&(data->flag), LS_P) && (S_ISDIR(op->file.st_mode)))
		ft_stprintf(KEEP_PF, "/");
	if (test_bit(&(data->flag), LS_M) && op->next)
		ft_stprintf(KEEP_PF, ",");
}

static void		print_name(t_ls *data, t_lsop *op, t_pad *pad, char *path)
{
//	if (test_bit(&(data->flag), LS_A_MAJ) &&
//				(!ft_strcmp(".", op->name) || !ft_strcmp("..", op->name)))
//		return ;
	if (test_bit(&(data->flag), LS_S))
		ft_stprintf(KEEP_PF, "%*d ", pad->block, op->file.st_blocks);
	if (test_bit(&(data->flag), LS_L))
		file_info(data, op, pad, path);
	if (test_bit(&(data->flag), LS_G_MAJ))
	{
		if ((op->file.st_mode & S_ISVTX && op->xattr <= 0) ||
				(S_ISCHR(op->file.st_mode)))
			ft_stprintf(KEEP_PF, "%s%s", B_YELLOW, T_BLACK);
		else if (op->file.st_mode & S_ISGID && op->file.st_mode & S_IXOTH)
			ft_stprintf(KEEP_PF, "%s%s", B_RED, T_BLACK);
		else if (S_ISDIR(op->file.st_mode))
			ft_stprintf(KEEP_PF, "%s", F_BOLD);
		else if (S_ISLNK(op->file.st_mode))
			ft_stprintf(KEEP_PF, "%s", T_PURPLE);
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP ||
				op->file.st_mode & S_IXOTH)
			ft_stprintf(KEEP_PF, "%s", T_RED);
	}
}

t_bool    print_file(t_ls *data, t_lsop *lst, t_pad *pad, char *path)
{
    t_lsop  *mem;

    mem = lst;
	if (!test_bit(&(data->flag), LS_F))
    	ls_sort(data, lst);
    while (mem)
    {
        print_name(data, mem, pad, path);
        print_extra(data, mem);
        if (!print_link(data, mem, pad, path))
            return (false);
        mem = mem->next;
    }
	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_1))
		ft_stprintf(KEEP_PF, "\n");
    return (true);
}