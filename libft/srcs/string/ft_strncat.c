/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcat.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:59:00 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 18:05:30 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t count_s1;
	size_t count_s2;

	count_s1 = 0;
	count_s2 = 0;
	while (s1[count_s1] != '\0')
		count_s1++;
	while (s2[count_s2] != '\0' && count_s2 < n)
	{
		s1[count_s1] = s2[count_s2];
		count_s1++;
		count_s2++;
	}
	s1[count_s1] = '\0';
	return (s1);
}
