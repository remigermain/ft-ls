/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:04:12 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap_elem2(t_lsop ***mem_n, t_lsop ***mem2_n)
{
	t_lsop	**mem;
	t_lsop	**mem2;
	t_stat	tmp_stat;
	char	mem_name[256];

	mem = (*mem_n);
	mem2 = (*mem2_n);
	tmp_stat = (*mem)->file;
	ft_memcpy(mem_name, (*mem)->name, 256);
	//tmp_name = (*mem)->name;
	(*mem)->file = (*mem2)->file;
	ft_memcpy((*mem)->name, (*mem2)->name, 256);
//	(*mem)->name = (*mem2)->name;
	(*mem2)->file = tmp_stat;
	ft_memcpy((*mem2)->name, mem_name, 256);
//	(*mem2)->name = tmp_name;
	ft_swap(&((*mem)->xattr), &((*mem2)->xattr));
}

static int	swap_elem(t_ls *data, t_lsop ***mem, t_lsop ***mem2)
{
	if (test_bit(&(data->flag), LS_R))
		swap_elem2(mem, mem2);
	else if (!test_bit(&(data->flag), LS_R))
		swap_elem2(mem2, mem);
	return (-1);
}

static void	ls_sort_funct(t_ls *data, t_lsop **op, int len,
		int (*sort_function)(t_ls*, t_lsop**, t_lsop**))
{
	t_lsop	**mem;
	t_lsop	**mem2;
	int		i;

	i = 1;
	while (i < len && (i = 1))
	{
		mem = op;
		mem2 = &((*op)->next);
		while (i < len && (*mem2))
		{
			if (sort_function(data, mem, mem2))
				i += swap_elem(data, &mem, &mem2);
			else
			{
				i++;
				mem = &((*mem)->next);
				mem2 = &((*mem2)->next);
			}
		}
	}
}

void		ls_sort(t_ls *data, t_lsop **op)
{
	t_lsop *mem;
	int len;

	mem = (*op);
	len = 0;
	while (mem && (++len))
		mem = mem->next;
	if (test_bit(&(data->flag), LS_T))
		ls_sort_funct(data, op, len, ls_sort_mtime);
	else if (test_bit(&(data->flag), LS_S_MAJ))
		ls_sort_funct(data, op, len, ls_sort_size);
	else if (test_bit(&(data->flag), LS_U))
		ls_sort_funct(data, op, len, ls_sort_atime);
	else if (test_bit(&(data->flag), LS_U_MAJ))
		ls_sort_funct(data, op, len, ls_sort_ctime);
	else
		ls_sort_funct(data, op, len, ls_sort_ascii);
}
