/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:04 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:05 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <unistd.h>
# include "../libftprintf/ft_printf.h"

# define DWORD unsigned int
# define RESERVE_FOR_PADDING 64
# define SINGLE_BIT 128
# define MD5_HASH_BIT 128

typedef struct	s_hash_buffer
{
	DWORD	a;
	DWORD	b;
	DWORD	c;
	DWORD	d;
}				t_hash_buffer;

typedef struct	s_md5
{
	size_t			original_bit_len;
	size_t			original_byte_len;
	size_t			variable_bit_len;
	t_hash_buffer	buffer;
	uint32_t		aa;
	uint32_t		bb;
	uint32_t		cc;
	uint32_t		dd;
}				t_md5;

u_char			*md5(const unsigned char *d, unsigned long n, \
					unsigned char *md);
void			adding_message_length(unsigned char *message, t_md5 *md5);
void			md5_msg_preprocess(u_char **msg, const u_char *orig_msg, \
					t_md5 *md5);
void			write_block_to_words(unsigned int *x, unsigned char *block);
u_int			leftrotate(unsigned int f, unsigned int s0);

#endif
