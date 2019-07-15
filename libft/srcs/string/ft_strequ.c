/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strequ.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 12:25:50 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 19:05:15 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int count;

	count = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[count] != '\0' && s2[count] != '\0')
	{
		if (s1[count] == s2[count])
			count++;
		else
			return (0);
	}
	if (s1[count] == s2[count])
		return (1);
	else
		return (0);
}
