/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchar.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:06:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 11:07:45 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		locat;
	int		locat_on;
	int		count;
	char	*dest;

	locat = 0;
	locat_on = 0;
	count = 0;
	dest = (char*)s;
	while (dest[count] != '\0')
	{
		if (dest[count] == (char)c)
		{
			locat = count;
			locat_on = 1;
		}
		count++;
	}
	if (dest[count] == (char)c)
		return (dest + count);
	if (locat_on == 1)
		return (dest + locat);
	return (NULL);
}
