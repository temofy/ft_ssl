/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:23 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:24 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sha.h"

const uint32_t g_k_sha256[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void	sha256_msg_preprocess(u_char **msg, const u_char *orig_msg, t_sha *sha)
{
	size_t		i;
	uint32_t	block;

	*msg = (u_char*)ft_memalloc(sha->original_byte_len
		+ RESERVE_FOR_PADDING);
	ft_memcpy(*msg, orig_msg, sha->original_byte_len);
	(*msg)[sha->original_byte_len] = SINGLE_BIT;
	sha->variable_bit_len = sha->original_bit_len + 1;
	while (sha->variable_bit_len % 512 != 448)
		sha->variable_bit_len++;
	i = -1;
	while (++i < ((sha->variable_bit_len / 8) / 4))
	{
		ft_memcpy((void*)&block, &((*msg)[i * 4]), 4);
		block = reverse_order_word(block);
		ft_memcpy(&((*msg)[i * 4]), &block, 4);
	}
	ft_bzero(&((*msg)[sha->variable_bit_len / 8]), 4);
	ft_memcpy(&((*msg)[sha->variable_bit_len / 8 + 4]),
		&sha->original_bit_len, 4);
	sha->variable_bit_len += 64;
}

void	sha256_main_loop(uint32_t *w, t_sha *sha)
{
	int i;

	i = -1;
	while (++i < 64)
	{
		sha->s1 = rigthrotate(sha->e, 6) ^ rigthrotate(sha->e, 11)
			^ rigthrotate(sha->e, 25);
		sha->ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->temp1 = sha->h + sha->s1 + sha->ch + g_k_sha256[i]
			+ w[i];
		sha->s0 = rigthrotate(sha->a, 2) ^ rigthrotate(sha->a, 13)
			^ rigthrotate(sha->a, 22);
		sha->maj = (sha->a & sha->b) ^ (sha->a & sha->c)
			^ (sha->b & sha->c);
		sha->temp2 = sha->s0 + sha->maj;
		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + sha->temp1;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = sha->temp1 + sha->temp2;
	}
}

void	handle_chunk(unsigned char *message, t_sha *sha, size_t nbr_chunk)
{
	uint32_t	w[64];
	int			j;

	write_block_to_words(w, message + 64 * nbr_chunk);
	j = 16;
	while (j < 64)
	{
		sha->s0 = rigthrotate(w[j - 15], 7) ^
		rigthrotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
		sha->s1 = rigthrotate(w[j - 2], 17) ^
		rigthrotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
		w[j] = w[j - 16] + sha->s0 + w[j - 7] + sha->s1;
		j++;
	}
	init_working_variables(sha);
	sha256_main_loop(w, sha);
	add_compressed_chunk_to_hash(sha);
}

void	calculate_sha256_hash(unsigned char *message, t_sha *sha)
{
	size_t	nbr_chunk;
	size_t	chunks_number;

	nbr_chunk = -1;
	chunks_number = sha->variable_bit_len / 512;
	while (++nbr_chunk < chunks_number)
		handle_chunk(message, sha, nbr_chunk);
}

u_char	*sha256(const u_char *d, size_t n, unsigned char *md)
{
	u_char	*message;
	t_sha	sha;
	int		i;

	sha256_init(&sha);
	sha.original_byte_len = n;
	sha.original_bit_len = n * 8;
	sha256_msg_preprocess(&message, d, &sha);
	calculate_sha256_hash(message, &sha);
	ft_memdel((void**)&message);
	if ((md = (unsigned char *)malloc(sizeof(unsigned char) * 32)) == NULL)
		return (NULL);
	i = -1;
	while (++i < 8)
		sha.h_a[i] = reverse_order_word(sha.h_a[i]);
	ft_memcpy(md, (void*)sha.h_a, 32);
	return (md);
}
