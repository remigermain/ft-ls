/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 15:53:01 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 15:53:05 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t a;

	a = 0;
	if (!dest || !src)
		return (0);
	while (src[a] != '\0' && size > 1)
	{
		dest[a] = src[a];
		a++;
		size--;
	}
	if (size > 0)
		dest[a] = '\0';
	return (ft_strlen(src));
}
