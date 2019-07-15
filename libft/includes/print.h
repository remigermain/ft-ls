/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 18:10:38 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 18:27:03 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

int				ft_putchar(char c);
int				ft_putchar_fd(char c, int fd);
int				ft_putpchar_fd(char c, int fd);
int				ft_putwchar(wchar_t c);
int				ft_putwchar_fd(wchar_t c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_base(int n, int base);
void			ft_putnbr_fd(int n, int fd);
int				ft_putstr(char const *str);
int				ft_putnstr(char const *str, int len);
int				ft_putstr_fd(char const *s, int fd);
int				ft_putnstr_fd(char const *s, int len, int fd);
int				ft_putpstr_fd(char const *s, int fd);
int				ft_putpnstr_fd(char const *s, int len, int fd);
int				ft_putstrw(wchar_t const *str);
int				ft_putnstrw(wchar_t const *str, int len);
int				ft_putstrw_fd(wchar_t const *s, int fd);
int				ft_putnstrw_fd(wchar_t const *s, int len, int fd);
void			ft_printtab(char **tab);
void			ft_printtab_fd(char **tab, int fd);
int				ft_maxlen_tab(char **tab, int index);

#endif
