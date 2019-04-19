/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 11:36:42 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ls(t_ls *data, t_lsop **op, t_padding *padding, int nb)
{
	t_lsop	*mem;

	ls_sort(data, op, nb);
	mem = (*op);
	while (mem->next)
	{
		if (test_bit(&(data->flag), 2) || mem->dir->d_name[0] != '.')
			read_file(data, mem, padding);
		mem = mem->next;
	}
	ft_printf("\n");
}

void	read_dir(t_ls *data, char *base, char *path)
{
	t_padding	pad;
	t_lsop	*op;
	t_lsop	*mem;
	void	*dir_ptr;
	char	*name;
	long	total;
	char	*rep;
	char	*rep2;
	int		len;

	len = 0;
	ft_bzero(&(pad), sizeof(t_padding));
	name = ft_strjoin(path, base);
	if (!(op = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_ls(data);
	mem = op;
	op->next = NULL;
	if ((dir_ptr = opendir(name)))
	{
		total = 0;
		if (!(rep2 = ft_strjoin(name, "/")))
			error_ls(data);
		while ((op->dir = readdir(dir_ptr)))
		{
			if (!(rep = ft_strjoin(rep2 , op->dir->d_name)))
				error_ls(data);
			stat(rep, &(op->file));
			if (test_bit(&(data->flag), 2) || op->dir->d_name[0] != '.')
				padding_ls(data, &pad, op);
			total += op->file.st_blocks;
			if (!(op->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				error_ls(data);
			op = op->next;
			op->next = NULL;
			len++;
			ft_memdel((void**)&rep);
		}
		ft_memdel((void**)&rep2);
		if ((test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11)) && data->indi)
			ft_printf("\n%s:\n", name);
		data->indi = 1;
		if (test_bit(&(data->flag), 0))
			ft_printf("total %d\n", total);
		print_ls(data, &mem, &pad, len);
		while (mem->next)
		{
			if (test_bit(&(data->flag), 1) && S_ISDIR(mem->file.st_mode) && ft_strlen(mem->dir->d_name)
				&& ft_strcmp(".", mem->dir->d_name) && ft_strcmp("..", mem->dir->d_name))
			{
				if (ft_strlen(mem->dir->d_name))
					read_dir(data, mem->dir->d_name, ft_strjoin(name, "/"));
			}
			op = mem;
			mem = mem->next;
			ft_memdel((void**)&op);
		}
		ft_memdel((void**)&mem);
		closedir(dir_ptr);
	}
	else
		ft_lserror(data, name);
	ft_memdel((void**)&name);
	if (path && path[0])
		ft_memdel((void**)&path);
	ft_memdel((void**)&op);
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
	return (0);
}
