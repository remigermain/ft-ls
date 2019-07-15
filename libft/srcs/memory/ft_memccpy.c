/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 19:19:53 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 20:01:49 by alepercq    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				count;

	count = 0;
	while (n-- > 0)
	{
		((unsigned char*)dest)[count] = ((unsigned char*)src)[count];
		if (((unsigned char*)src)[count] == (unsigned char)c)
			return (dest + count + 1);
		count++;
	}
	return (NULL);
}
