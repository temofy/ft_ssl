/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:02:44 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:02:45 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libftprintf/ft_printf.h"

void	write_block_to_words(unsigned int *x, unsigned char *block)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < 16)
	{
		ft_memcpy(&x[i], (block + size), 4);
		size += 4;
		i++;
	}
}

void	write_block_to_words64(uint64_t *x, u_char *block)
{
	uint32_t	i;
	uint32_t	size;

	i = 0;
	size = 0;
	while (i < 16)
	{
		ft_memcpy(&x[i], (block + size), 8);
		size += 8;
		i++;
	}
}
