/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:18 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:19 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/md5.h"

const unsigned int g_s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

const unsigned int g_k_md5[] = {0xd76aa478, 0xe8c7b756, 0x242070db,
	0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
	0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
	0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,
	0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87,
	0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942,
	0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
	0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039,
	0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7,
	0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f,
	0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
	0xeb86d391};

void	md5_main_algo(t_md5 *md5, int32_t j, uint32_t *f, uint32_t *k)
{
	if (j >= 0 && j <= 15)
	{
		*f = ((md5->bb & md5->cc) | (~md5->bb & md5->dd));
		*k = j;
	}
	else if (j >= 16 && j <= 31)
	{
		*f = ((md5->bb & md5->dd) | (md5->cc & ~md5->dd));
		*k = (5 * j + 1) % 16;
	}
	else if (j >= 32 && j <= 47)
	{
		*f = (md5->bb ^ md5->cc ^ md5->dd);
		*k = (3 * j + 5) % 16;
	}
	else if (j >= 48 && j <= 63)
	{
		*f = (md5->cc ^ (md5->bb | ~md5->dd));
		*k = (7 * j) % 16;
	}
}

void	md5_main_loop(uint32_t *x, t_md5 *md5)
{
	int32_t		j;
	uint32_t	f;
	uint32_t	k;

	j = -1;
	k = 0;
	f = 0;
	while (++j < 64)
	{
		md5_main_algo(md5, j, &f, &k);
		f = f + md5->aa + g_k_md5[j] + x[k];
		md5->aa = md5->dd;
		md5->dd = md5->cc;
		md5->cc = md5->bb;
		md5->bb = md5->bb + leftrotate(f, g_s[j]);
	}
}

void	handle_md5_chunk(unsigned char *message, t_md5 *md5, size_t nbr_chunk)
{
	unsigned int x[16];

	md5->aa = md5->buffer.a;
	md5->bb = md5->buffer.b;
	md5->cc = md5->buffer.c;
	md5->dd = md5->buffer.d;
	write_block_to_words(x, message + 64 * nbr_chunk);
	md5_main_loop(x, md5);
	md5->buffer.a = md5->buffer.a + md5->aa;
	md5->buffer.b = md5->buffer.b + md5->bb;
	md5->buffer.c = md5->buffer.c + md5->cc;
	md5->buffer.d = md5->buffer.d + md5->dd;
}

void	calculate_md5_hash(unsigned char *message, t_md5 *md5)
{
	size_t	i;
	size_t	chunks_number;

	md5->buffer.a = 0x67452301;
	md5->buffer.b = 0xefcdab89;
	md5->buffer.c = 0x98badcfe;
	md5->buffer.d = 0x10325476;
	i = -1;
	chunks_number = md5->variable_bit_len / 512;
	while (++i < chunks_number)
		handle_md5_chunk(message, md5, i);
}

u_char	*md5(const unsigned char *d, unsigned long n, unsigned char *md)
{
	u_char	*message;
	t_md5	md5;

	md5.original_byte_len = n;
	md5.original_bit_len = n * 8;
	md5_msg_preprocess(&message, d, &md5);
	adding_message_length(message, &md5);
	calculate_md5_hash(message, &md5);
	ft_memdel((void**)&message);
	md = (unsigned char *)malloc(sizeof(unsigned char) * 16);
	ft_memcpy(md, &md5.buffer, 16);
	return (md);
}
