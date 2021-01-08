/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:16 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:17 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/md5.h"

void	adding_message_length(unsigned char *message, t_md5 *md5)
{
	message += md5->variable_bit_len / 8;
	ft_memcpy((void*)message, &md5->original_bit_len, 8);
	md5->variable_bit_len += 64;
}

void	md5_msg_preprocess(u_char **msg, const u_char *orig_msg, t_md5 *md5)
{
	size_t	i;

	*msg = (unsigned char*)malloc(sizeof(unsigned char)
		* (md5->original_byte_len + RESERVE_FOR_PADDING));
	ft_bzero((*msg) + md5->original_byte_len, sizeof(unsigned char)
		* (RESERVE_FOR_PADDING));
	i = -1;
	while (++i < md5->original_byte_len)
	{
		(*msg)[i] = orig_msg[i];
	}
	(*msg)[i] = SINGLE_BIT;
	md5->variable_bit_len = md5->original_bit_len;
	md5->variable_bit_len++;
	while (1)
	{
		if (md5->variable_bit_len % 512 == 448)
			break ;
		md5->variable_bit_len++;
	}
}
