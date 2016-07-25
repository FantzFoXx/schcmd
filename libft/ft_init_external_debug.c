/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_external_debug.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 14:59:39 by udelorme          #+#    #+#             */
/*   Updated: 2016/04/22 17:19:50 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"

int		ft_init_external_debug(char *filename, int verbose)
{
	int fd;
	if (!filename)
		fd = open("debug", O_RDWR);
	else
		fd = open(filename, O_APPEND, O_RDWR);
	if (fd == -1)
		return (-1);
	if (verbose)
	{
		ft_putendl("You have invoked the ft_init_external_debug function.\n\nThis function is a debug function and is not made for production.\n\nIf no filename has been linked, or if the filename does not exists,\nthe function will create a file in the dir of the binary file.\n\nYou can't run multiple external debugs concurently\nYou MUST remove this function when your debug is finished\n");
	}
	ft_external_debug(NULL, fd);
	ft_close_external_debug(fd);
	return (fd);
}
