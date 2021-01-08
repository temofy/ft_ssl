/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:29 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:03:30 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sha.h"

void	sha256_init(t_sha *sha)
{
	memset(sha, 0, sizeof(*sha));
	sha->h_a[0] = 0x6a09e667;
	sha->h_a[1] = 0xbb67ae85;
	sha->h_a[2] = 0x3c6ef372;
	sha->h_a[3] = 0xa54ff53a;
	sha->h_a[4] = 0x510e527f;
	sha->h_a[5] = 0x9b05688c;
	sha->h_a[6] = 0x1f83d9ab;
	sha->h_a[7] = 0x5be0cd19;
}

void	init_working_variables(t_sha *sha)
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

void	add_compressed_chunk_to_hash(t_sha *sha)
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
