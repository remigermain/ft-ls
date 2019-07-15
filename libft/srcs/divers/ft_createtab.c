/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_createtab.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/02 11:44:53 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 12:31:16 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_createtab(int len, char c)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (!(tab[i] = (char*)ft_memalloc(len + 1)))
		{
			ft_memdeltab_char(&tab);
			return (NULL);
		}
		ft_memset(tab[i++], c, len);
	}
	tab[i] = NULL;
	return (tab);
}
