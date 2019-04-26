/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 12:04:31 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_sort_size(t_ls *data, t_lsop **op, int len, int i)
{
	t_lsop **mem;
	t_lsop **mem2;

	while (i < len && (i = 1))
	{
		mem = op;
		mem2 = &((*op)->next);
		while (i < len && (*mem2))
		{
			if ((test_bit(&(data->flag), LS_R) &&
				(*mem)->file.st_size > (*mem2)->file.st_size) ||
					(!test_bit(&(data->flag), LS_R) &&
				(*mem)->file.st_size < (*mem2)->file.st_size))
				i += swap_elem(data, op, &mem, &mem2);
			else if ((*mem)->file.st_size == (*mem2)->file.st_size)
				i += ls_sort_ascii(data, op, &mem, &mem2);
			else
			{
				i++;
				mem = &((*mem)->next);
				mem2 = &((*mem2)->next);
			}
		}
	}
}

static void	ls_sort_atime(t_ls *data, t_lsop **op, int len, int i)
{
	t_lsop **mem;
	t_lsop **mem2;

	while (i < len && (i = 1))
	{
		mem = op;
		mem2 = &((*op)->next);
		while (i < len && (*mem2))
		{
			if ((test_bit(&(data->flag), LS_R) &&
				(*mem)->file.st_atime > (*mem2)->file.st_atime) ||
					(!test_bit(&(data->flag), LS_R) &&
				(*mem)->file.st_atime < (*mem2)->file.st_atime))
				i += swap_elem(data, op, &mem, &mem2);
			else if ((*mem)->file.st_atime == (*mem2)->file.st_atime)
				i += ls_sort_ascii(data, op, &mem, &mem2);
			else
			{
				i++;
				mem = &((*mem)->next);
				mem2 = &((*mem2)->next);
			}
		}
	}
}

static void	ls_sort_time(t_ls *data, t_lsop **op, int len, int i)
{
	t_lsop **mem;
	t_lsop **mem2;

	while (i < len && (i = 1))
	{
		mem = op;
		mem2 = &((*op)->next);
		while (i < len && (*mem2))
		{
			if ((test_bit(&(data->flag), LS_R) &&
				(*mem)->file.st_ctime > (*mem2)->file.st_ctime) ||
					(!test_bit(&(data->flag), LS_R) &&
				(*mem)->file.st_ctime < (*mem2)->file.st_ctime))
				i += swap_elem(data, op, &mem, &mem2);
			else if ((*mem)->file.st_ctime == (*mem2)->file.st_ctime)
				i += ls_sort_ascii(data, op, &mem, &mem2);
			else
			{
				i++;
				mem = &((*mem)->next);
				mem2 = &((*mem2)->next);
			}
		}
	}
}

static void	ls_sort_alpha(t_ls *data, t_lsop **op, int len, int i)
{
	t_lsop **mem;
	t_lsop **mem2;

	while (i < len && (i = 1))
	{
		mem = op;
		mem2 = &((*op)->next);
		while (i < len && (*mem2))
			i += ls_sort_ascii(data, op, &mem, &mem2);
	}
}

void		ls_sort(t_ls *data, t_lsop **op, int len)
{
	if (test_bit(&(data->flag), LS_T))
		ls_sort_time(data, op, len, 1);
	else if (test_bit(&(data->flag), LS_U))
		ls_sort_atime(data, op, len, 1);
	else if (test_bit(&(data->flag), LS_S_MAJ))
		ls_sort_size(data, op, len, 1);
	else
		ls_sort_alpha(data, op, len, 1);
}
