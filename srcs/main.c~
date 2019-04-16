#include "ft_ls.h"

void	set_bit(short *st, int i)
{
	(*st) ^= 1 << i;
}

t_bool	test_bit(short *st, int i)
{
	if ((*st) & 1 << i)
		return (TRUE);
	return (FALSE);
}


static	int	put_flags(t_ls *st, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_bzero(st, sizeof(t_ls));
	while (argc > 1 && argv[1][0] == '-' && argv[1][++i])
	{
		if (argv[1][i] == 'l')
			set_bit(&(st->flag), 0);
		else if (argv[1][i] == 'R')
			set_bit(&(st->flag), 1);
		else if (argv[1][i] == 'a')
			set_bit(&(st->flag), 2);
		else if (argv[1][i] == 'r')
			set_bit(&(st->flag), 3);
		else if (argv[1][i] == 't')
			set_bit(&(st->flag), 4);
		else if (argv[1][i] == 'u')
			set_bit(&(st->flag), 5);
		else if (argv[1][i] == 'f')
			set_bit(&(st->flag), 6);
		else if (argv[1][i] == 'g')
			set_bit(&(st->flag), 7);
		else if (argv[1][i] == 'd')
			set_bit(&(st->flag), 8);
		else if (argv[1][i] == 'G')
			set_bit(&(st->flag), 9);
	}
	return (i == -1 ? 1 : 2);
}

void	read_dir(t_ls *st, char *base, char *path)
{
	t_stat	stat_dir;
	t_dir	*dir;
	void	*dir_ptr;
	char	*name;

	name = ft_strjoin(path, base);
	if ((dir_ptr = opendir(name)))
	{
		if (st->indice)
			ft_printf("\n");
		st->indice = 1;
		if (test_bit(&(st->flag), 1))
			ft_printf("%s:\ntotal:  \n", base);
		while ((dir = readdir(dir_ptr)))
		{
			if (test_bit(&(st->flag), 1) && opendir(ft_strjoin(ft_strjoin(name, "/"), dir->d_name)) &&
					ft_strcmp("..", dir->d_name) && ft_strcmp(".", dir->d_name))
				read_dir(st, dir->d_name, ft_strjoin(name, "/"));
			else
				read_file(st, dir->d_name, ft_strjoin(name, "/"));
		}
		closedir(dir_ptr);
	}
	else
		read_file(st, base, path);
	st->indice = 1;
	ft_memdel((void**)&name);
}

void	read_file(t_ls *st, char *base, char *path)
{
	t_stat	stat_file;
	char	*name;

	name = ft_strjoin(path, base);
	if (test_bit(&(st->flag), 2) || (base[0] && base[0] != '.'))
	{
		stat(name, &(stat_file));
		if (test_bit(&(st->flag), 0))
		{
			file_right(stat_file);
			file_link(stat_file);
			file_group(stat_file);
			file_size(stat_file);
			file_date(stat_file);
		}
		ft_printf("%s", base);
		if (test_bit(&(st->flag), 0))
			ft_printf("\n");
	}
}


int main(int argc, char **argv)
{
	t_ls	st;
	int	i;
	int	j;
	char	*name;

	i = put_flags(&st, argc, argv);
	j = 0;
	if (i == argc && (argc++))
		j = 1;
	while (i < argc)
	{
		if (j)
			st.name = strdup(".");
		else
			st.name = ft_strdup(argv[i]);
		read_dir(&st, st.name, "");
		if (++i != argc)
			ft_printf("\n");
	}
	free_ftls(&st);
	return (0);
}
