/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:07 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:08 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA_H
# define FT_SHA_H

# include <unistd.h>
# include <stdint.h>
# include "../libftprintf/ft_printf.h"

# define RESERVE_FOR_PADDING 64
# define RESERVE_FOR_LONG_PADDING 128
# define SINGLE_BIT 128
# define SHA224_HASH_BIT 224
# define SHA256_HASH_BIT 256
# define SHA512_HASH_BIT 512

typedef struct	s_sha
{
	uint32_t		original_bit_len;
	uint32_t		original_byte_len;
	uint32_t		variable_bit_len;
	uint32_t		h_a[8];
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		ch;
	uint32_t		maj;
	uint32_t		temp1;
	uint32_t		temp2;
}				t_sha;

typedef struct	s_sha5
{
	uint64_t		original_bit_len;
	uint64_t		original_byte_len;
	uint64_t		variable_bit_len;
	uint64_t		h_a[8];
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
	uint64_t		s0;
	uint64_t		s1;
	uint64_t		ch;
	uint64_t		maj;
	uint64_t		temp1;
	uint64_t		temp2;
}				t_sha5;

void			write_block_to_words(unsigned int *x, unsigned char *block);
void			write_block_to_words64(uint64_t *x, u_char *block);

void			sha256_msg_preprocess(u_char **msg, const u_char *orig_msg, \
					t_sha *sha);
void			sha256_main_loop(uint32_t *w, t_sha *sha);
void			init_working_variables(t_sha *sha);
void			add_compressed_chunk_to_hash(t_sha *sha);
void			handle_chunk(unsigned char *message, t_sha *sha, \
					size_t nbr_chunk);
void			calculate_sha256_hash(unsigned char *message, t_sha *sha);

void			sha256_init(t_sha *sha);
void			sha512_init(t_sha5 *sha);
void			init_working_variables(t_sha *sha);
void			init_working_variables512(t_sha5 *sha);
void			add_compressed_chunk_to_hash(t_sha *sha);
void			add_compressed_chunk_to_hash512(t_sha5 *sha);

unsigned char	*sha224(const unsigned char *d, size_t n, unsigned char *md);
unsigned char	*sha256(const unsigned char *d, size_t n, unsigned char *md);
unsigned char	*sha512(const unsigned char *d, size_t n, unsigned char *md);
uint32_t		reverse_order_word(uint32_t n);
uint64_t		reverse_order_2word(uint64_t n);
uint32_t		rigthrotate(uint32_t x, uint32_t n);
uint64_t		rigthrotate64(uint64_t x, uint64_t n);

#endif
