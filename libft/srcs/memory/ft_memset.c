/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   memset.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 16:02:07 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:16:55 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	t_uchar	*dest;

	i = 0;
	dest = (unsigned char*)b;
	while (i < len)
		dest[i++] = (unsigned char)c;
	return (b);
}
