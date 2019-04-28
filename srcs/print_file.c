/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 02:28:12 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int		print_link(t_ls *data, t_lsop *op, t_padding *pad)
{
	char	buff[1024];
	char	*name;
	int		i;

	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_M) &&
			!test_bit(&(data->flag), LS_1))
		ft_printf(" %*@", pad->name - ft_strlen(op->name), "char", ' ');
	else if (test_bit(&(data->flag), LS_M))
		ft_printf(" ");
	if (S_ISLNK(op->file.st_mode) && test_bit(&(data->flag), LS_L))
	{
		if (!(name = ft_strjoin(data->path, op->name)))
			error_ls();
		if ((i = readlink(name, buff, 1023)) > 0)
			ft_printf(" -> %.*s", i, buff);
		ft_memdel((void**)&name);
	}
	if (test_bit(&(data->flag), LS_L) || test_bit(&(data->flag), LS_1))
		ft_printf("\n");
	return (1);
}

static int		print_extra(t_ls *data, t_lsop *op, t_padding *padding)
{
	if (!(op->next))
		padding->name = 0;
	if (test_bit(&(data->flag), LS_A) || op->name[0] != '.')
		ft_printf("%s", op->name);
	if (test_bit(&(data->flag), LS_G_MAJ))
		ft_printf("%s", T_WHITE);
	if (test_bit(&(data->flag), LS_F_MAJ))
	{
		if (S_ISDIR(op->file.st_mode))
			ft_printf("/");
		else if (S_ISFIFO(op->file.st_mode))
			ft_printf("|");
		else if (S_ISLNK(op->file.st_mode))
			ft_printf("@");
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP ||
				op->file.st_mode & S_IXOTH)
			ft_printf("*");
	}
	else if (test_bit(&(data->flag), LS_P) && (S_ISDIR(op->file.st_mode)))
		ft_printf("/");
	if (test_bit(&(data->flag), LS_M) && op->next)
		ft_printf(",");
	return (print_link(data, op, padding));
}

static int		print_name(t_ls *data, t_lsop *op, t_padding *padding)
{
	if (test_bit(&(data->flag), LS_A_MAJ) &&
				(!ft_strcmp(".", op->name) || !ft_strcmp("..", op->name)))
		return (0);
	if (test_bit(&(data->flag), LS_L))
		file_info(data, op, padding);
	if (test_bit(&(data->flag), LS_G_MAJ))
	{
		if (op->file.st_mode & S_ISVTX && op->xattr <= 0)
			ft_printf("%s%s", B_YELLOW, T_BLACK);
		else if (S_ISDIR(op->file.st_mode))
			ft_printf("%s", F_BOLD);
		else if (S_ISLNK(op->file.st_mode))
			ft_printf("%s", T_PURPLE);
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP ||
				op->file.st_mode & S_IXOTH)
			ft_printf("%s", T_RED);
	}
	return (print_extra(data, op, padding));
}

static void		print_ls(t_ls *data, t_lsop **op, t_padding *pad, int len)
{
	t_lsop	*mem;
	int		i;

	if (!test_bit(&(data->flag), LS_F))
		ls_sort(data, op, len);
	mem = (*op);
	i = 0;
	data->indi = 0;
	while (mem)
	{
		if ((test_bit(&(data->flag), LS_A) || mem->name[0] != '.') && (i = 1))
			print_name(data, mem, pad);
		mem = mem->next;
	}
	if (!test_bit(&(data->flag), LS_L) && !test_bit(&(data->flag), LS_1))
		ft_printf("\n");
	data->indi = i;
}

void			print_file(t_ls *data, t_lsop **mem, t_padding *pad,
		t_lsdiv *div)
{
	if (data->indi && !data->link_dir)
		ft_printf("\n");
	if ((test_bit(&(data->flag), LS_R_MAJ) || test_bit(&(data->flag), LS_F_MAJ)
				|| data->argc > 1) && data->indi && !data->link_dir)
		ft_printf("%s:\n", div->name);
	data->indi = 1;
	if (test_bit(&(data->flag), LS_L) && !data->link_dir)
		ft_printf("total %d\n", div->total);
	print_ls(data, mem, pad, div->len);
	data->link_dir = 0;
}
