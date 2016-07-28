#include "libft.h"
#include "get_next_line_gz.h"
#include "shrcmd.h"
#include <unistd.h>
#include <dirent.h>
#include "zlib.h"
#include <stdio.h>

int		read_mode_select(gzFile manpage, int fd_manpage, char **buf)
{
	if (manpage)
		return (get_next_line_gz(&manpage, buf));
	else if (fd_manpage)
		return (get_next_line(fd_manpage, buf));
	return (-1);
}

int		*create_associate_tab_search(int size_tab)
{
	int		*tab_values = NULL;

	tab_values = (int *)malloc(sizeof(int) * size_tab);
	ft_bzero(tab_values, sizeof(tab_values));
	return (tab_values);
}

int		check_matches(int **matches, int size)
{
	int		ret = 0;
	int		i = 0;

	while (i < size)
	{
		if ((*matches)[i] == 0)
		{
			ret = 0;
			break ;
		}
		else
			ret += (*matches)[i];
		i++;
	}
	free(*matches);
	return (ret);
}

int		search_expr(char **search, gzFile manpage, int fd_manpage)
{
	char	*buf = NULL;
	char	*ret_chr = NULL;
	int		i = 0;
	int		*tab_values;

	tab_values = create_associate_tab_search(ft_tab_size(search));
	while (read_mode_select(manpage, fd_manpage, &buf) > 0)
	{
		while (search[i])
		{
			ret_chr = ft_strstr(buf, search[i]);
			if (ret_chr != NULL)
				tab_values[i] += 1;
			i++;
		}
		i = 0;
		free(buf);
	}
	return (check_matches(&tab_values, ft_tab_size(search)));
}

char	**get_man_path_environ(void)
{
	char	*tmp = NULL;
	char	**ret = NULL;

	tmp = getenv("MANPATH");
	if (tmp)
		ret = ft_strsplit(tmp, ':');
	else
	{
		ret = (char **)malloc(sizeof(char *) * 3);
		ret[0] = "/usr/share/man/man1/";
		ret[1] = "/usr/share/man/man8/";
		ret[2] = NULL;
	}
	return (ret);
}

t_cmd_meta *get_all_files(char	**man_path)
{
	int				i = 0;
	DIR				*dir = NULL;
	struct dirent	*meta_dir = NULL;
	t_cmd_meta		*all_files = NULL;
	t_cmd_meta		*index;
	char			*complete_filename = NULL;

	while (man_path[i])
	{
		dir = opendir(man_path[i]);
		if (dir)
		{
			while ((meta_dir = readdir(dir)) != NULL)
			{
				complete_filename = ft_strjoin(man_path[i], meta_dir->d_name);
				cmd_meta_push(&all_files, cmd_meta_new(complete_filename));
				ft_strdel(&complete_filename);
			}
			closedir(dir);
		}
		i++;
	}
	index = all_files;
	return (all_files);
}

int		print_command_name(char *filename)
{
	int		i_beg = 0;
	int		i_end = 0;

	i_beg = ft_index_lmatch(filename, '/') + 1;
	if (i_beg)
	{
		i_end = ft_index_fmatch(filename, '.');
		if (i_beg < i_end)
		{
			write(1, &filename[i_beg], i_end - i_beg);
			return (1);
		}
	}
	return (0);
}

void	print_command_data(t_cmd_meta *file)
{
	if (print_command_name(file->filename))
		printf(" : %d matchs\n", file->match_count);
}

void	search_in_files(t_cmd_meta *files, char **keywords)
{
	gzFile		file = NULL;
	int			fd_file = 0;

	ft_putendl("Commands found : ");
	while (files)
	{
		if (files->filename[ft_index_lmatch(files->filename, '/') + 1] != '.')
		{
			if (ft_strstr(files->filename, ".gz"))
				file = gzopen(files->filename, "r");
			else
				fd_file = open(files->filename, O_RDONLY);
		}
		if (file || fd_file)
		{
			if ((files->match_count = search_expr(keywords, file, fd_file)))
				print_command_data(files);
			if (file)
				gzclose(file);
			else if (fd_file)
				close(fd_file);
			fd_file = 0;
			file = NULL;
		}
		files = files->next;
	}
}

char	**expand_keywords(char	**keywords)
{
	int	i = 1;
	char	**expanded = NULL;
	char	*new_value = NULL;

	expanded = (char **)malloc(sizeof(char *) * ft_tab_size(keywords));
	while (keywords[i])
	{
		new_value = ft_strnew(ft_strlen(keywords[i]) + 2);
		ft_strcat(new_value, " ");
		ft_strcat(new_value, keywords[i]);
		ft_strcat(new_value, " ");
		expanded[i - 1] = new_value;
		expanded[i] = NULL;
		i++;
	}
	return (expanded);
}

int		shrcmd(char **av)
{
	char	**man_path = NULL;
	char	**keywords = NULL;
	t_cmd_meta	*files;
	t_cmd_meta	*bak;

	man_path = get_man_path_environ();
	bak = files = get_all_files(man_path);
	keywords = expand_keywords(av);
	search_in_files(files, keywords);
	return (0);
}
