/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:06:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 20:05:29 by alepercq    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*dest;

	count = 0;
	dest = (char*)s;
	while (dest[count] != '\0')
	{
		if (dest[count] == (char)c)
			return (dest + count);
		count++;
	}
	if (dest[count] == (char)c)
		return (dest + count);
	return (NULL);
}
