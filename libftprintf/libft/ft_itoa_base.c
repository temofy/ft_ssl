/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temofy <temofy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:00:55 by cheller           #+#    #+#             */
/*   Updated: 2020/09/10 00:17:04 by temofy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calculate_len(int n, int base)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		len++;
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char		*ft_itoa_base(int value, int base)
{
	char	*str;
	int		i;
	char	*tab;

	tab = "0123456789ABCDEF";
	if (base < 2 || base > 16)
		return (0);
	i = calculate_len(value, base) - 1;
	str = ft_strnew(calculate_len(value, base));
	if (value == 0)
		return (ft_strncpy(str, "0", 1));
	if (value < 0 && base == 10)
	{
		str[0] = '-';
		value = value * -1;
	}
	while (value > 0)
	{
		str[i--] = tab[ft_abs(value % base)];
		value /= base;
	}
	return (str);
}
