/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 10:13:44 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_sort_size(t_ls *data, t_lsop **op)
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
			swap_elem(data, op, &mem, &mem2);
		else if ((*mem)->file.st_size == (*mem2)->file.st_size)
			ls_sort_ascii(data, op, &mem, &mem2);
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

static void	ls_sort_atime(t_ls *data, t_lsop **op)
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
			swap_elem(data, op, &mem, &mem2);
		else if ((*mem)->file.st_atime == (*mem2)->file.st_atime)
			ls_sort_ascii(data, op, &mem, &mem2);
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

static void	ls_sort_time(t_ls *data, t_lsop **op)
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
			swap_elem(data, op, &mem, &mem2);
		else if ((*mem)->file.st_ctime == (*mem2)->file.st_ctime)
			ls_sort_ascii(data, op, &mem, &mem2);
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

static void	ls_sort_alpha(t_ls *data, t_lsop **op)
{
	t_lsop **mem;
	t_lsop **mem2;

	mem = op;
	mem2 = &((*op)->next);
	while ((*mem2)->next)
		ls_sort_ascii(data, op, &mem, &mem2);
}

void		ls_sort(t_ls *data, t_lsop **op)
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
