/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 18:10:38 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 18:26:52 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H
# define ABS(a)				(a < 0 ? -a : a)
# define MAX(a, b)			(a < b ? b : a)
# define MIN(a, b)			(a < b ? a : b)

int				ft_is_prime(int nb);
int				ft_find_next_prime(int nb);
int				ft_is_prime(int nb);
int				ft_iterative_factorial(int nb);
int				ft_iterative_power(int nb, int power);
int				ft_recursive_factorial(int nb);
int				ft_recursive_power(int nb, int power);
int				ft_sqrt(int nb);
int				ft_intlen(int n);
int				ft_intlen_base(int n, int base);

#endif
