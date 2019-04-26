/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 13:34:36 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_elem2(t_lsop ***mem_n, t_lsop ***mem2_n)
{
	t_lsop	**mem;
	t_lsop	**mem2;
	t_stat	tmp_stat;
	t_dir	*tmp_dir;
	char	*tmp_name;

	mem = (*mem_n);
	mem2 = (*mem2_n);
	tmp_stat = (*mem)->file;
//	tmp_dir = (*mem)->dir;
	tmp_name = (*mem)->name;
	(*mem)->file = (*mem2)->file;
//	(*mem)->dir = (*mem2)->dir;
	(*mem)->name = (*mem2)->name;
	(*mem2)->file = tmp_stat;
//	(*mem2)->dir = tmp_dir;
	(*mem2)->name = tmp_name;
}

int		swap_elem(t_ls *data, t_lsop **op, t_lsop ***mem, t_lsop ***mem2)
{
	if (test_bit(&(data->flag), LS_R))
		swap_elem2(mem, mem2);
	else if (!test_bit(&(data->flag), LS_R))
		swap_elem2(mem2, mem);
	return (-1);
}

int		ls_sort_ascii(t_ls *data, t_lsop **op, t_lsop ***mem, t_lsop ***mem2)
{
	int	i;

	i = 0;
	while ((**mem)->name && (**mem2)->name &&
			(**mem)->name[i] == (**mem2)->name[i])
		i++;
	if ((**mem)->name && (**mem2)->name &&
		 ((test_bit(&(data->flag), LS_R) &&
		(**mem)->name[i] < (**mem2)->name[i]) ||
			(!test_bit(&(data->flag), LS_R) &&
			(**mem)->name[i] > (**mem2)->name[i])))
		return (swap_elem(data, op, mem, mem2));
	else
	{
		*mem = &((**mem)->next);
		*mem2 = &((**mem2)->next);
		return (1);
	}
	return (0);
}
