/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strequ.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 12:25:50 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 19:28:13 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int count;

	count = 0;
	if (!s1 || (!s2 && n > 0))
		return (0);
	while (s1[count] != '\0' && s2[count] != '\0' && count < ((int)n - 1))
	{
		if (s1[count] == s2[count])
			count++;
		else
			return (0);
	}
	if (s1[count] == s2[count] || n == 0)
		return (1);
	else
		return (0);
}
