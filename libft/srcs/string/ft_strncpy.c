/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:40:42 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 18:21:18 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int count;

	count = 0;
	while (src[count] != '\0' && count < (int)len)
	{
		dst[count] = (char)src[count];
		count++;
	}
	while (count < (int)len)
		dst[count++] = '\0';
	return (dst);
}
