/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichel <mmichel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 20:52:37 by mmichel           #+#    #+#             */
/*   Updated: 2016/05/28 14:57:22 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_debug.h"

void	ft_debug_common(const char *fonc, int li, const char *fc, const char *n)
{
	ft_putstr_width(fonc, 30);
	ft_putstr(":\t");
	ft_putnbr_width(li, 5);
	if (n)
	{
		ft_putstr(":\t");
		ft_putstr_width(n, 20);
		ft_putstr(" = ");
	}
	else
		ft_putstr(fc);
}

void	ft_debugstr(const char *str)
{
	char	*ptr;

	ptr = (char *)str;
	if (str && *str)
		ft_putstr_width(str, 20);
	else
		ft_putstr_width("[nil]", 20);
	if (!(ptr = ft_ultoa_base((unsigned long)ptr, "0123456789ABCDEF")))
		return ;
	ft_putstr(" 0x");
	ft_putstr(ptr);
	ft_putchar('\n');
	free(ptr);
}

void	ft_debugc(const char c)
{
	ft_putchar(c);
	ft_putchar('\n');
}

void	ft_debugptr(void *ptr)
{
	char	*str;

	if (!(str = ft_ltoa_base((long)ptr, "0123456789ABCDEF")))
		return ;
	ft_putstr("0x");
	ft_putstr(str);
	ft_putchar('\n');
	free(str);
}
