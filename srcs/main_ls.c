/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 09:43:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_dir(t_ls *data, char *base, char *path)
{
	t_padding	pad;
	t_dir		*tmp_dir;
	t_lsop		*op;
	t_lsop		*mem;
	void		*dir_ptr;
	char		*name;
	long		total;
	char		*rep;
	char		*rep2;
	int			len;

	len = 0;
	ft_bzero(&(pad), sizeof(t_padding));
	name = ft_strjoin(path, base);
	op = NULL;
	if ((dir_ptr = opendir(name)))
	{
		total = 0;
		if (!(rep2 = ft_strjoin(name, "/")))
			error_ls(data);
		while (1)
		{
			if (!op)
			{
				if (!(op = (t_lsop*)malloc(sizeof(t_lsop))))
					error_ls(data);
				op->next = NULL;
				mem = op;
			}
			else if (!op->next)
			{
				if (!((op->next) = (t_lsop*)malloc(sizeof(t_lsop))))
					error_ls(data);
				op = op->next;
				op->next = NULL;
			}
			if (!(tmp_dir = readdir(dir_ptr)))
				break ;
			if (!(op->dir = (t_dir*)ft_memalloc(sizeof(t_dir))))
				error_ls(data);
			ft_memcpy(op->dir, tmp_dir, sizeof(t_dir));
			if (!(rep = ft_strjoin(rep2 , op->dir->d_name)))
				error_ls(data);
			lstat(rep, &(op->file));
			op->name = op->dir->d_name;
			if (test_bit(&(data->flag), 2) || op->dir->d_name[0] != '.')
				padding_ls(data, &pad, op);
			total += op->file.st_blocks;
			len++;
		}
		if ((test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11)) && data->indi)
			ft_printf("\n%s:\n", name);
		data->indi = 1;
		if (test_bit(&(data->flag), 0))
			ft_printf("total %d\n", total);
		print_ls(data, &mem, &pad, len);
		while (mem->next)
		{
			if (test_bit(&(data->flag), 1) && (S_ISDIR(mem->file.st_mode))
				&& ft_strcmp(".", mem->dir->d_name) && ft_strcmp("..", mem->dir->d_name))
			{
				if (mem->dir->d_name[0])
					read_dir(data, mem->dir->d_name, ft_strjoin(name, "/"));
			}
			op = mem;
			mem = mem->next;
		}
		closedir(dir_ptr);
	}
	else
	{
		if ((test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11)) && data->indi)
		{
			ft_printf("\n%s:\n", name);
			ft_lserror(data, base);
		}
		else
			ft_lserror(data, name);
	}
}
