/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:40 by cheller           #+#    #+#             */
/*   Updated: 2021/01/08 18:44:16 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sha.h"

const uint64_t	g_k_sha512[] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c,
	0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694, 0xe49b69c19ef14ad2,
	0xEfbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2,
	0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b, 0xa2bfe8a14cf10364,
	0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a,
	0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72,
	0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae,
	0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 0x4cc5d4becb3e42b6,
	0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

void	sha512_msg_preprocess(u_char **msg, const u_char *orig_msg, t_sha5 *sha)
{
	size_t		i;
	uint64_t	block;

	*msg = (u_char*)ft_memalloc(sha->original_byte_len
		+ RESERVE_FOR_LONG_PADDING);
	ft_memcpy(*msg, orig_msg, sha->original_byte_len);
	(*msg)[sha->original_byte_len] = SINGLE_BIT;
	sha->variable_bit_len = sha->original_bit_len + 1;
	while (sha->variable_bit_len % 1024 != 896)
		sha->variable_bit_len++;
	i = -1;
	while (++i < ((sha->variable_bit_len / 8) / 8))
	{
		ft_memcpy((void*)&block, &((*msg)[i * 8]), 8);
		block = reverse_order_2word(block);
		ft_memcpy(&((*msg)[i * 8]), &block, 8);
	}
	ft_bzero(&((*msg)[sha->variable_bit_len / 8]), 8);
	ft_memcpy(&((*msg)[sha->variable_bit_len / 8 + 8]),
		&sha->original_bit_len, 8);
	sha->variable_bit_len += 128;
}

void	sha512_main_loop(uint64_t *w, t_sha5 *sha)
{
	int i;

	i = -1;
	while (++i < 80)
	{
		sha->s1 = rigthrotate64(sha->e, 14) ^ rigthrotate64(sha->e, 18)
			^ rigthrotate64(sha->e, 41);
		sha->ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->temp1 = sha->h + sha->s1 + sha->ch + g_k_sha512[i]
			+ w[i];
		sha->s0 = rigthrotate64(sha->a, 28) ^ rigthrotate64(sha->a, 34)
			^ rigthrotate64(sha->a, 39);
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

void	handle_chunk1024(unsigned char *message, t_sha5 *sha, size_t nbr_chunk)
{
	uint64_t	w[80];
	int			j;

	write_block_to_words64(w, message + 128 * nbr_chunk);
	j = 16;
	while (j < 80)
	{
		sha->s0 = rigthrotate64(w[j - 15], 1) ^
		rigthrotate64(w[j - 15], 8) ^ (w[j - 15] >> 7);
		sha->s1 = rigthrotate64(w[j - 2], 19) ^
		rigthrotate64(w[j - 2], 61) ^ (w[j - 2] >> 6);
		w[j] = w[j - 16] + sha->s0 + w[j - 7] + sha->s1;
		j++;
	}
	init_working_variables512(sha);
	sha512_main_loop(w, sha);
	add_compressed_chunk_to_hash512(sha);
}

void	calculate_sha512_hash(unsigned char *message, t_sha5 *sha)
{
	size_t	nbr_chunk;
	size_t	chunks_number;

	nbr_chunk = -1;
	chunks_number = sha->variable_bit_len / 1024;
	while (++nbr_chunk < chunks_number)
		handle_chunk1024(message, sha, nbr_chunk);
}

u_char	*sha512(const unsigned char *d, size_t n, unsigned char *md)
{
	u_char		*message;
	t_sha5		sha;
	int			i;

	sha512_init(&sha);
	sha.original_byte_len = n;
	sha.original_bit_len = n * 8;
	sha512_msg_preprocess(&message, d, &sha);
	calculate_sha512_hash(message, &sha);
	ft_memdel((void**)&message);
	if ((md = (unsigned char *)malloc(sizeof(unsigned char) * 64)) == NULL)
		return (NULL);
	i = -1;
	while (++i < 8)
		sha.h_a[i] = reverse_order_2word(sha.h_a[i]);
	ft_memcpy(md, (void*)sha.h_a, 64);
	return (md);
}
