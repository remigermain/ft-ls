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

t_bool			file_acl(t_lsop *op, char *path)
{
	acl_entry_t	dummy;
	acl_t		acl;
	char		*path_total;

	if (exist_flags(LS_L))
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

static t_bool	print_link(t_lsop *op, t_pad *pad, char *path, t_winsize win)
{
	char	buff[1024];
	char	*path_new;
	int		i;

	if (!exist_flags(LS_L) && !exist_flags(LS_M) &&
			!exist_flags(LS_1) &&
			(pad->col + pad->name) < win.ws_col)
		ft_stprintf(KEEP_PF, " %*@", pad->name - ft_strlen(op->name),
				"char", ' ');
	else if (exist_flags(LS_M))
		ft_stprintf(KEEP_PF, " ");
	if (S_ISLNK(op->file.st_mode) && exist_flags(LS_L))
	{
		if (!(path_new = cat_path(op->name, path)))
			return (FALSE);
		if ((i = readlink(path_new, buff, 1023)) > 0)
			ft_stprintf(KEEP_PF, " -> %.*s", i, buff);
		ft_memdel((void**)&path_new);
	}
	return (TRUE);
}

static void		print_extra(t_lsop *op)
{
	ft_stprintf(KEEP_PF, "%s", op->name);
	if (exist_flags(LS_G_MAJ))
		ft_stprintf(KEEP_PF, "%s", T_WHITE);
	if (exist_flags(LS_F_MAJ))
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
	else if (exist_flags(LS_P) && (S_ISDIR(op->file.st_mode)))
		ft_stprintf(KEEP_PF, "/");
	if (exist_flags(LS_M) && op->next)
		ft_stprintf(KEEP_PF, ",");
}

static t_bool	print_name(t_lsop *op, t_pad *pad, char *path)
{
	if (exist_flags(LS_S))
		ft_stprintf(KEEP_PF, "%*d ", pad->block, op->file.st_blocks);
	if (exist_flags(LS_L) && !file_info(op, pad, path))
		return (FALSE);
	if (exist_flags(LS_G_MAJ))
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

t_bool			print_file(t_lsop *lst, t_pad *pad, char *path)
{
	static t_winsize win;
	t_lsop	*mem;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	ls_sort(lst);
	mem = lst;
	while (mem)
	{
		pad->col += (exist_flags(LS_M) ? ft_strlen(mem->name) + 2 : pad->name);
		if (!print_name(mem, pad, path))
			return (FALSE);
		print_extra(mem);
		if (!print_link(mem, pad, path, win))
			return (FALSE);
		if (exist_flags(LS_L) || exist_flags(LS_1) || !mem->next)
			ft_stprintf(KEEP_PF, "\n");
		else if (!exist_flags(LS_1) && !exist_flags(LS_L))
		{
			if (!exist_flags(LS_M) && (pad->col + pad->name + 1)
				> win.ws_col && (pad->col = 0) != -1)
				ft_stprintf(KEEP_PF, "\n");
			else if (exist_flags(LS_M) && (pad->col + 
			ft_strlen(mem->name) + 2) > win.ws_col && (pad->col = 0) != -1)
				ft_stprintf(KEEP_PF, "\n");
		}
		
		mem = mem->next;
	}
	return (TRUE);
}