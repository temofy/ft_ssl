/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:01:59 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:02:00 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libftprintf/ft_printf.h"

uint32_t	leftrotate(unsigned int f, unsigned int s0)
{
	return (((f) << (s0)) | ((f) >> (32 - (s0))));
}

uint32_t	rigthrotate(uint32_t x, uint32_t n)
{
	return ((((unsigned int)x >> n)) | (x << (32 - n)));
}

uint64_t	rigthrotate64(uint64_t x, uint64_t n)
{
	return (((x >> n)) | (x << (64 - n)));
}

uint32_t	reverse_order_word(uint32_t n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

uint64_t	reverse_order_2word(uint64_t n)
{
	return ((n & 0xff00000000000000) >> 56 \
			| (n & 0x00ff000000000000) >> 40 \
			| (n & 0x0000ff0000000000) >> 24 \
			| (n & 0x000000ff00000000) >> 8 \
			| (n & 0x00000000ff000000) << 8 \
			| (n & 0x0000000000ff0000) << 24 \
			| (n & 0x000000000000ff00) << 40 \
			| (n & 0x00000000000000ff) << 56);
}
