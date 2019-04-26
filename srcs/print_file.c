/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 14:42:08 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_link(t_ls *data, t_lsop *op)
{
	if (test_bit(&(data->flag), LS_M) && op->next)
		ft_printf(", ");
//	if ((test_bit(&(data->flag), LS_1) || test_bit(&(data->flag), LS_L))
//			&& op->next)
		ft_printf("\n");
	return (1);
}

static int	print_extra(t_ls *data, t_lsop *op, t_padding *padding)
{
	if (!(op->next))
		padding->name = 0;
	if ((!test_bit(&(data->flag), LS_M) && !test_bit(&(data->flag), LS_1) &&
				(!test_bit(&(data->flag), LS_L))) || data->flag == 0)
		ft_printf("%-*s", padding->name + 1, op->name);
	else if (test_bit(&(data->flag), 2) || op->name[0] != '.')
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
	return (print_link(data, op));
}

static int	print_file(t_ls *data, t_lsop *op, t_padding *padding)
{
	if (test_bit(&(data->flag), LS_A_MAJ) &&
				(!ft_strcmp(".", op->name) || !ft_strcmp("..", op->name)))
		return (0);
	if (test_bit(&(data->flag), LS_L))
	{
		file_right(data, op->file, padding);
		file_link(data, op->file, padding);
		file_group(data, op->file, padding);
		file_size(data, op->file, padding);
		file_date(data, op->file, padding);
	}
	if (test_bit(&(data->flag), LS_G_MAJ))
	{
		if (S_ISDIR(op->file.st_mode))
			ft_printf("%s", F_BOLD);
		else if (S_ISLNK(op->file.st_mode))
			ft_printf("%s", T_PURPLE);
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP ||
				op->file.st_mode & S_IXOTH)
			ft_printf("%s", T_RED);
	}
	return (print_extra(data, op, padding));
}

void		print_ls(t_ls *data, t_lsop **op, t_padding *pad, int len)
{
	t_lsop	*mem;
	int		i;

	ls_sort(data, op, len);
	mem = (*op);
	i = 0;
	data->indi = 0;
	while (mem)
	{
		if ((test_bit(&(data->flag), LS_A) || mem->name[0] != '.') && (i = 1))
			print_file(data, mem, pad);
		mem = mem->next;
	}
	data->indi = i;
}
