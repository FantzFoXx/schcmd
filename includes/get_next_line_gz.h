/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <udelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 15:50:39 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/12 11:24:14 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_GZ_H
# define GET_NEXT_LINE_GZ_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "zlib.h"

typedef struct	s_gzfile
{
	gzFile			*fd;
	int				read;
	char			tmp[BUFF_SIZE + 1];
	char			*buf;
	struct s_gzfile	*next;
}				t_gzfile;

int				get_next_line_gz(gzFile *fd, char **line);

#endif
