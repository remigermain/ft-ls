/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 12:28:42 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int	read_file2(t_ls *data, t_lsop *op, t_padding *padding)
{
	if (test_bit(&(data->flag), 9))
		ft_printf("%s", T_WHITE);
	if (test_bit(&(data->flag), 11))
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
	if (test_bit(&(data->flag), LS_M) && op->next && op->next->next)
		ft_printf(", ");
	if ((test_bit(&(data->flag), LS_1) || test_bit(&(data->flag), LS_L))
			&& op->next && op->next->next)
		ft_printf("\n");
	return (1);
}

int	read_file(t_ls *data, t_lsop *op, t_padding *padding)
{
	if (test_bit(&(data->flag), LS_A_MAJ) &&
				(!ft_strcmp(".", op->dir->d_name) || !ft_strcmp("..", op->dir->d_name)))
		return (0);
	if (test_bit(&(data->flag), 0))
	{
		file_right(data, op->file, padding);
		file_link(data, op->file, padding);
		file_group(data, op->file, padding);
		file_size(data, op->file, padding);
		file_date(data, op->file, padding);
	}
	if (test_bit(&(data->flag), 9))
	{
		if (S_ISDIR(op->file.st_mode))
				ft_printf("%s", F_BOLD);
		else if (S_ISLNK(op->file.st_mode))
				ft_printf("%s", T_PURPLE);
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP || 
				op->file.st_mode & S_IXOTH)
			ft_printf("%s", T_RED);
	}
	if (op->next && !op->next->next)
		padding->name = 0;
	if ((!test_bit(&(data->flag), LS_M) && !test_bit(&(data->flag), LS_1)) || data->flag == 0)
		ft_printf("%-*s", padding->name + 1, op->dir->d_name);
	else if (test_bit(&(data->flag), 2) || op->dir->d_name[0] != '.')
		ft_printf("%s", op->dir->d_name);	
	return (read_file2(data, op, padding));
}

void	print_ls(t_ls *data, t_lsop **op, t_padding *padding, int len)
{
	t_lsop	*mem;
	int		i;

	ls_sort(data, op, len);
	mem = (*op);
	i = 0;
	while (mem->next)
	{
		if ((test_bit(&(data->flag), 2) || mem->dir->d_name[0] != '.') && (++i))
			read_file(data, mem, padding);
		mem = mem->next;
	}
	if (i)
		ft_printf("\n");
}
