/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 10:59:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 18:21:44 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int count;
	int count2;

	count = 0;
	count2 = 0;
	while (haystack[count] != '\0' && count < (int)len)
	{
		while (haystack[count + count2] == needle[count2] &&
				haystack[count + count2] != '\0' && (count + count2) < (int)len)
			count2++;
		if (needle[count2] == '\0')
			return ((char*)haystack + count);
		count++;
		count2 = 0;
	}
	return (NULL);
}
