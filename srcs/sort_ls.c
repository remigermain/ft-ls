/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 09:41:49 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		swap_elem(t_lsop **mem, t_lsop **mem2)
{
	t_stat	tmp_stat;
	t_dir	*tmp_dir;
	char	*tmp_name;

	tmp_stat = (*mem)->file;
	tmp_dir = (*mem)->dir;
	tmp_name = (*mem)->name;
	(*mem)->file = (*mem2)->file;
	(*mem)->dir = (*mem2)->dir;
	(*mem)->name = (*mem2)->name;
	(*mem2)->file = tmp_stat;
	(*mem2)->dir = tmp_dir;
	(*mem2)->name = tmp_name;
}

void	ls_sort_ascii(t_ls *data, t_lsop **op, t_lsop ***mem, t_lsop ***mem2)
{
	int	i;

	i = 0;
	while ((**mem)->dir->d_name[i] && (**mem2)->dir->d_name[i] &&
			(**mem)->dir->d_name[i] == (**mem2)->dir->d_name[i])
		i++;
	if ((test_bit(&(data->flag), LS_R) &&
		(**mem)->dir->d_name[i] < (**mem2)->dir->d_name[i]) ||
			(!test_bit(&(data->flag), LS_R) &&
		(**mem)->dir->d_name[i] > (**mem2)->dir->d_name[i]))
	{
		if (test_bit(&(data->flag), LS_R))
			swap_elem(*mem, *mem2);
		else if (!test_bit(&(data->flag), LS_R))
			swap_elem(*mem2, *mem);
		*mem = op;
		*mem2 = &((*op)->next);
	}
	else
	{
		*mem = &((**mem)->next);
		*mem2 = &((**mem2)->next);
	}
}

void			ls_sort_size(t_ls *data, t_lsop **op)
{
	t_lsop **mem;
	t_lsop **mem2;

	mem = op;
	mem2 = &((*op)->next);
	while ((*mem2)->next)
	{
		if ((test_bit(&(data->flag), LS_R) &&
			(*mem)->file.st_size > (*mem2)->file.st_size) ||
				(!test_bit(&(data->flag), LS_R) &&
			(*mem)->file.st_size < (*mem2)->file.st_size))
		{
			if (test_bit(&(data->flag), LS_R))
				swap_elem(mem, mem2);
			else if (!test_bit(&(data->flag), LS_R))
				swap_elem(mem2, mem);
			mem = op;
			mem2 = &((*op)->next);
		}
		else if ((*mem)->file.st_size == (*mem2)->file.st_size)
			ls_sort_ascii(data, op, &mem, &mem2);
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

void			ls_sort_atime(t_ls *data, t_lsop **op)
{
	t_lsop **mem;
	t_lsop **mem2;

	mem = op;
	mem2 = &((*op)->next);
	while ((*mem2)->next)
	{
		if ((test_bit(&(data->flag), LS_R) &&
			(*mem)->file.st_atime > (*mem2)->file.st_atime) ||
				(!test_bit(&(data->flag), LS_R) &&
			(*mem)->file.st_atime < (*mem2)->file.st_atime))
		{
			if (test_bit(&(data->flag), LS_R))
				swap_elem(mem, mem2);
			else if (!test_bit(&(data->flag), LS_R))
				swap_elem(mem2, mem);
			mem = op;
			mem2 = &((*op)->next);
		}
		else if ((*mem)->file.st_atime == (*mem2)->file.st_atime)
			ls_sort_ascii(data, op, &mem, &mem2);
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

void			ls_sort_time(t_ls *data, t_lsop **op)
{
	t_lsop **mem;
	t_lsop **mem2;

	mem = op;
	mem2 = &((*op)->next);
	while ((*mem2)->next)
	{
		if ((test_bit(&(data->flag), LS_R) &&
			(*mem)->file.st_ctime > (*mem2)->file.st_ctime) ||
				(!test_bit(&(data->flag), LS_R) &&
			(*mem)->file.st_ctime < (*mem2)->file.st_ctime))
		{
			if (test_bit(&(data->flag), LS_R))
				swap_elem(mem, mem2);
			else if (!test_bit(&(data->flag), LS_R))
				swap_elem(mem2, mem);
			mem = op;
			mem2 = &((*op)->next);
		}
		else if ((*mem)->file.st_ctime == (*mem2)->file.st_ctime)
			ls_sort_ascii(data, op, &mem, &mem2);
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

void			ls_sort_alpha(t_ls *data, t_lsop **op)
{
	int i;
	t_lsop **mem;
	t_lsop **mem2;
	t_lsop **tmp;

	mem = op;
	mem2 = &((*op)->next);
	while ((*mem2)->next)
	{
		i = 0;
		while ((*mem)->dir->d_name[i] && (*mem2)->dir->d_name[i] &&
				(*mem)->dir->d_name[i] == (*mem2)->dir->d_name[i])
			i++;
		if ((test_bit(&(data->flag), LS_R) &&
			(*mem)->dir->d_name[i] < (*mem2)->dir->d_name[i]) ||
				(!test_bit(&(data->flag), LS_R) &&
			(*mem)->dir->d_name[i] > (*mem2)->dir->d_name[i]))
		{
			if (test_bit(&(data->flag), LS_R))
				swap_elem(mem, mem2);
			else if (!test_bit(&(data->flag), LS_R))
				swap_elem(mem2, mem);
			mem = op;
			mem2 = &((*op)->next);
		}
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

void			ls_sort(t_ls *data, t_lsop **op)
{
	if (test_bit(&(data->flag), LS_T))
		ls_sort_time(data, op);
	else if (test_bit(&(data->flag), LS_U))
		ls_sort_atime(data, op);
	else if (test_bit(&(data->flag), LS_S_MAJ))
		ls_sort_size(data, op);	
	else
		ls_sort_alpha(data, op);
}
