/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:34:30 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 13:04:26 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	ft_memdeltab_int(int ***ap, int size)
{
	int count;

	count = 0;
	while ((*ap) && count < size)
		ft_memdel((void**)&((*ap)[count++]));
	ft_memdel((void**)ap);
}

void	ft_memdeltab_char(char ***ap)
{
	size_t count;

	count = 0;
	while ((*ap) && ((*ap)[count]))
		ft_memdel((void**)&((*ap)[count++]));
	ft_memdel((void**)ap);
}
