/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichel <mmichel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 21:01:18 by mmichel           #+#    #+#             */
/*   Updated: 2016/05/17 21:01:18 by mmichel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_debugnbr(int n)
{
	ft_putnbr(n);
	ft_putchar('\n');
}

void	ft_debugnbrl(long n)
{
	ft_putnbrl(n);
	ft_putchar('\n');
}

void	ft_debugnbrul(t_ul n, char *base)
{
	char	*str;

	if (!(str = ft_ultoa_base(n, base)))
		return ;
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
}
