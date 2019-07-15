/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:37:07 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:48 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *new;

	if (size > 2147483647 || (int)size < 0)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_memset(new, 0, size + 1);
	return (new);
}
