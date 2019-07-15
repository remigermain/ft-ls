/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_is_printable.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/06 12:06:59 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 15:12:59 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_printable(char *str)
{
	int a;

	a = 0;
	while (str[a] != '\0')
	{
		if (ft_isprint(str[a]))
			a++;
		else
			return (0);
	}
	return (1);
}
