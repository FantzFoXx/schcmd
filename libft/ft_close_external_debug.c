/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_external_debug.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 15:09:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/04/22 17:19:51 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <fcntl.h>
#include <unistd.h>

void	ft_close_external_debug(int fd)
{
	static int debug_fd = -1;
	if (debug_fd != -1)
		close(debug_fd);
	if (debug_fd == -1)
		debug_fd = fd;
}
