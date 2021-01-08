/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:35 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:37 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sha.h"

void	sha512_init(t_sha5 *sha)
{
	memset(sha, 0, sizeof(*sha));
	sha->h_a[0] = 0x6a09e667f3bcc908;
	sha->h_a[1] = 0xbb67ae8584caa73b;
	sha->h_a[2] = 0x3c6ef372fe94f82b;
	sha->h_a[3] = 0xa54ff53a5f1d36f1;
	sha->h_a[4] = 0x510e527fade682d1;
	sha->h_a[5] = 0x9b05688c2b3e6c1f;
	sha->h_a[6] = 0x1f83d9abfb41bd6b;
	sha->h_a[7] = 0x5be0cd19137e2179;
}

void	init_working_variables512(t_sha5 *sha)
{
	sha->a = sha->h_a[0];
	sha->b = sha->h_a[1];
	sha->c = sha->h_a[2];
	sha->d = sha->h_a[3];
	sha->e = sha->h_a[4];
	sha->f = sha->h_a[5];
	sha->g = sha->h_a[6];
	sha->h = sha->h_a[7];
}

void	add_compressed_chunk_to_hash512(t_sha5 *sha)
{
	sha->h_a[0] += sha->a;
	sha->h_a[1] += sha->b;
	sha->h_a[2] += sha->c;
	sha->h_a[3] += sha->d;
	sha->h_a[4] += sha->e;
	sha->h_a[5] += sha->f;
	sha->h_a[6] += sha->g;
	sha->h_a[7] += sha->h;
}
