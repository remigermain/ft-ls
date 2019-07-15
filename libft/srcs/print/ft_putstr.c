/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 16:24:32 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/19 18:52:01 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char const *str)
{
	return (ft_putstr_fd(str, 1));
}

int	ft_putnstr(char const *str, int len)
{
	return (ft_putnstr_fd(str, len, 1));
}

int	ft_putstrw(wchar_t const *str)
{
	return (ft_putstrw_fd(str, 1));
}

int	ft_putnstrw(wchar_t const *str, int len)
{
	return (ft_putnstrw_fd(str, len, 1));
}
