#include "shrcmd.h"
#include <unistd.h>
#include "libft.h"
#include <dirent.h>
#include "zlib.h"

int		read_mode_select(gzFile manpage, int fd_manpage, char *buf)
{
	if (manpage)
		return (gzread(manpage, buf, sizeof(buf) - 1));
	else if (fd_manpage)
		return (read(fd_manpage, buf, sizeof(buf) - 1));
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
	int		ret = 1;
	int		i = 0;

	while (i < size)
	{
		if ((*matches)[i] == 0)
			ret = 0;
		i++;
	}
	free(*matches);
	return (ret);
}

int		search_expr(char **search, gzFile manpage, int fd_manpage)
{
	char	buf[1024];
	char	*ret_chr = NULL;
	int		i = 0;
	int		*tab_values;

	bzero(buf, sizeof(buf));
	(void)search;
	tab_values = create_associate_tab_search(ft_tab_size(search));
	while (read_mode_select(manpage, fd_manpage, buf) > 0)
	{
		while (search[i])
		{
			ret_chr = strstr(buf, search[i]);
			if (ret_chr != NULL)
			{
				tab_values[i] = 1;
			}
			i++;
		}
		i = 0;
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
#if 0
	while (index)
	{
		ft_putstr("file found : ");
		ft_putendl(index->filename);
		index = index->next;
	}
#endif
	return (all_files);
}

void	search_in_files(t_cmd_meta *files, char **keywords)
{
	gzFile		file = NULL;
	int			fd_file = 0;

	while (files)
	{
		if (ft_strstr(files->filename, ".gz"))
			file = gzopen(files->filename, "r");
		else
			fd_file = open(files->filename, O_RDONLY);
		if (file || fd_file)
		{
			if (search_expr(keywords, file, fd_file))
				ft_putendl(files->filename);
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

int		shrcmd(int ac, char **av, char **environ)
{
	(void)ac;
	(void)environ;
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
