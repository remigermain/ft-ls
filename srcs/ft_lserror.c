#include "ft_ls.h"

void	ft_lserror(t_ls *data, char *name)
{
	data->error = TRUE;
	ft_printf("ft_ls: %s: %m\n", name);
}
