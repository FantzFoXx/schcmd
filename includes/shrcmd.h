
#ifndef SHRCMD_H
# define SHRCMD_H

#include "libft.h"
#include "zlib.h"

typedef struct	s_cmd_meta
{
	char				*filename;
	int					fd;
	int					match_count;
	struct s_cmd_meta	*next;
}				t_cmd_meta;

int			shrcmd(int ac, char **av, char **environ);
int			search_expr(char **search, gzFile manpage);
//int		search_expr(char **search, struct gzFile_s manpage);
void		cmd_meta_push(t_cmd_meta **first, t_cmd_meta *new);
t_cmd_meta	*cmd_meta_new(char	*filename);

#endif
