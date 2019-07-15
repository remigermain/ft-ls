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

static int		print_link(t_ls *data, t_lsop *op, t_padding *pad, int size)
{
	char	buff[1024];
	char	*name;
	int		i;

	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_M) &&
			!test_bit(&(data->flag), LS_1) && op->next &&
			(size + pad->name) < data->w.ws_col)
		ft_stprintf(KEEP_PF, " %*@", pad->name - ft_strlen(op->name),
				"char", ' ');
	else if (test_bit(&(data->flag), LS_M))
		ft_stprintf(KEEP_PF, " ");
	if (S_ISLNK(op->file.st_mode) && test_bit(&(data->flag), LS_L))
	{
		if (!(name = ft_strjoin(data->path, op->name)))
			error_ls();
		if ((i = readlink(name, buff, 1023)) > 0)
			ft_stprintf(KEEP_PF, " -> %.*s", i, buff);
		ft_memdel((void**)&name);
	}
	if (test_bit(&(data->flag), LS_L) || test_bit(&(data->flag), LS_1))
		ft_stprintf(KEEP_PF, "\n");
	ft_stprintf(OUT_PF, "");
	return (1);
}

static int		print_extra(t_ls *data, t_lsop *op, t_padding *pad, int size)
{
	if (!(op->next))
		pad->name = 0;
	if (test_bit(&(data->flag), LS_A) || op->name[0] != '.')
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
	return (print_link(data, op, pad, size));
}

static int		print_name(t_ls *data, t_lsop *op, t_padding *padding, int size)
{
	if (test_bit(&(data->flag), LS_A_MAJ) &&
				(!ft_strcmp(".", op->name) || !ft_strcmp("..", op->name)))
		return (0);
	if (test_bit(&(data->flag), LS_L))
		file_info(data, op, padding);
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
	return (print_extra(data, op, padding, size));
}

static void		print_ls(t_ls *data, t_lsop **op, t_padding *pad, int len)
{
	t_lsop	*mem;
	int		i;
	int		size;

	if (!test_bit(&(data->flag), LS_F))
		ls_sort(data, op, len);
	mem = (*op);
	i = 0;
	data->indi = 0;
	size = 0;
	while (mem)
	{
		if ((test_bit(&(data->flag), LS_A) || mem->name[0] != '.') && (i = 1))
		{
			size += pad->name;
			print_name(data, mem, pad, size);
			if (!test_bit(&(data->flag), LS_1) && !test_bit(&(data->flag), LS_L)
					&& (size + pad->name) > data->w.ws_col && (size = 0) != 1)
				ft_stprintf(KEEP_PF, "\n");
		}
		mem = mem->next;
	}
	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_1))
		ft_stprintf(KEEP_PF, "\n");
	data->indi = i;
}

void			print_file(t_ls *data, t_lsop **mem, t_padding *pad,
		t_lsdiv *div)
{
	data->level = 1;
	if (data->indi && !data->link_dir)
		ft_stprintf(KEEP_PF, "\n");
	if (test_bit(&(data->flag), LS_R_MAJ) || data->nb_arg)
		ft_stprintf(KEEP_PF, "%s:\n", div->name);
	data->indi = 1;
	if (test_bit(&(data->flag), LS_L) && !data->link_dir)
		ft_stprintf(KEEP_PF, "total %d\n", div->total);
	print_ls(data, mem, pad, div->len);
	data->link_dir = 0;
}
