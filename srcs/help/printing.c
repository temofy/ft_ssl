/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:11:51 by cheller           #+#    #+#             */
/*   Updated: 2021/01/08 18:30:45 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

char	*add0(char *hex)
{
	if (ft_strlen(hex) == 1)
		hex = ft_strfjoin("0", hex, 2);
	return (hex);
}

char	*convert_hash_to_str(u_char *hash, int bit_hash)
{
	char	*hash_str;
	char	*tmp;
	int		i;

	i = -1;
	hash_str = ft_strnew(0);
	while (++i < (bit_hash / 8))
	{
		tmp = ft_unsigned_itoa_base(hash[i], 16);
		tmp = add0(tmp);
		hash_str = ft_strfjoin(hash_str, tmp, 0);
	}
	hash_str = ft_str_tolower(hash_str);
	return (hash_str);
}
