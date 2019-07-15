/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_integer_table.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 11:26:31 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 17:59:31 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_integer_table(int *tab, int size)
{
	int a;
	int b;

	b = 0;
	a = size - 1;
	while (a != 0)
	{
		if (tab[a] > tab[a - 1])
		{
			b = tab[a];
			tab[a] = tab[a - 1];
			tab[a - 1] = b;
			a = size - 1;
		}
		else
			a--;
	}
}
