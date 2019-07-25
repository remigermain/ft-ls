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

t_bool			file_acl(t_ls *data, t_lsop *op, char *path)
{
	acl_entry_t	dummy;
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
	return (TRUE);
}

static t_bool	print_link(t_ls *data, t_lsop *op, t_pad *pad, char *path)
{
	char	buff[1024];
	char	*path_new;
	int		i;

	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_M) &&
			!test_bit(&(data->flag), LS_1) &&
			(pad->col + pad->name) < data->w.ws_col)
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
	return (TRUE);
}

static void		print_extra(t_ls *data, t_lsop *op)
{
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

static t_bool	print_name(t_ls *data, t_lsop *op, t_pad *pad, char *path)
{
	if (test_bit(&(data->flag), LS_S))
		ft_stprintf(KEEP_PF, "%*d ", pad->block, op->file.st_blocks);
	if (test_bit(&(data->flag), LS_L) && !file_info(data, op, pad, path))
		return (FALSE);
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
	return (TRUE);
}

t_bool			print_file(t_ls *data, t_lsop *lst, t_pad *pad, char *path)
{
	t_lsop	*mem;

	if (!test_bit(&(data->flag), LS_F))
		ls_sort(data, lst);
	mem = (test_bit(&(data->flag), LS_R) ? lst->last : lst);
	while (mem)
	{
		pad->col += pad->name;
		if (!print_name(data, mem, pad, path))
			return (FALSE);
		print_extra(data, mem);
		if (!print_link(data, mem, pad, path))
			return (FALSE);
		if (!test_bit(&(data->flag), LS_1) && !test_bit(&(data->flag), LS_L)
			&& (pad->col + pad->name + 1) > data->w.ws_col && (pad->col = 0) != -1)
			ft_stprintf(KEEP_PF, "\n");
		mem = (test_bit(&(data->flag), LS_R) ? mem->prev : mem->next);
	}
	if (!test_bit(&(data->flag), LS_L) &&
		!test_bit(&(data->flag), LS_1) && pad->col && !data->av)
		ft_stprintf(KEEP_PF, "\n");
	return (TRUE);
}
