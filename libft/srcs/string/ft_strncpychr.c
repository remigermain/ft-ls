/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpychr.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 14:59:00 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/08 15:21:27 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpychr(const char *s, int c)
{
	int count;
	int len;

	count = 0;
	len = ft_strlen(s);
	if (!s)
		return (NULL);
	while (s[count] != '\0' && s[count] != c)
		count++;
	if (s[count] == c)
		count++;
	if (count == len)
		return (NULL);
	return (ft_strsub(s, count, (len - count)));
}
