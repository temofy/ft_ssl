#include "../include/sha256.h"

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

void	sha256_init(t_sha256 *sha256)
{
    memset(sha256, 0, sizeof(*sha256));
    sha256->h_a[0] = 0x6a09e667;
    sha256->h_a[1] = 0xbb67ae85;
    sha256->h_a[2] = 0x3c6ef372;
    sha256->h_a[3] = 0xa54ff53a;
    sha256->h_a[4] = 0x510e527f;
    sha256->h_a[5] = 0x9b05688c;
    sha256->h_a[6] = 0x1f83d9ab;
    sha256->h_a[7] = 0x5be0cd19;
}

void	sha256_message_preprocess(unsigned char **message, const unsigned char *original_message, t_sha256 *sha256)
{
    size_t		i;
	uint32_t	block;

	*message = ft_memalloc(sha256->original_byte_len + RESERVE_FOR_PADDING);
	//*message = (u_char*)malloc(sizeof(u_char) * (sha256->original_byte_len + RESERVE_FOR_PADDING));
	ft_bzero((*message) + sha256->original_byte_len, sizeof(u_char) * (RESERVE_FOR_PADDING));
	ft_memcpy(*message, original_message, sha256->original_byte_len);
	(*message)[sha256->original_byte_len] = SINGLE_BIT;
	sha256->variable_bit_len = sha256->original_bit_len + 1;
	while (sha256->variable_bit_len % 512 != 448)
		sha256->variable_bit_len++;
	i = -1;
	while (++i < ((sha256->variable_bit_len / 8) / 4))
	{
		ft_memcpy((void*)&block, &((*message)[i * 4]), 4);
		block = reverse_order_word(block);
		ft_memcpy(&((*message)[i * 4]), &block, 4);
	}
	ft_bzero(&((*message)[sha256->variable_bit_len / 8]), 4);
	ft_memcpy(&((*message)[sha256->variable_bit_len / 8 + 4]),
		&sha256->original_bit_len, 4);
	sha256->variable_bit_len += 64;
}

void	sha256_main_loop(uint32_t *w, t_sha256 *sha256)
{
	int i;

	i = -1;
	while (++i < 64)
	{
		sha256->s1 = rigthrotate(sha256->e, 6) ^ rigthrotate(sha256->e, 11)
			^ rigthrotate(sha256->e, 25);
		sha256->ch = (sha256->e & sha256->f) ^ ((~sha256->e) & sha256->g);
		sha256->temp1 = sha256->h + sha256->s1 + sha256->ch + g_k_sha256[i]
			+ w[i];
		sha256->s0 = rigthrotate(sha256->a, 2) ^ rigthrotate(sha256->a, 13)
			^ rigthrotate(sha256->a, 22);
		sha256->maj = (sha256->a & sha256->b) ^ (sha256->a & sha256->c)
			^ (sha256->b & sha256->c);
		sha256->temp2 = sha256->s0 + sha256->maj;
		sha256->h = sha256->g;
		sha256->g = sha256->f;
		sha256->f = sha256->e;
		sha256->e = sha256->d + sha256->temp1;
		sha256->d = sha256->c;
		sha256->c = sha256->b;
		sha256->b = sha256->a;
		sha256->a = sha256->temp1 + sha256->temp2;
	}
}

void	calculate_sha256_hash(unsigned char *message, t_sha256 *sha256)
{
	size_t	i;
	size_t	chunks_number;

	i = -1;
	chunks_number = sha256->variable_bit_len / 512;
	while (++i < chunks_number)
	{
		int j;
		uint32_t	w[64];

		write_block_to_words(w, message + 64 * i);
		j = 16;
		while (j < 64)
		{
			sha256->s0 = rigthrotate(w[j - 15], 7) ^
			rigthrotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
			sha256->s1 = rigthrotate(w[j - 2], 17) ^
			rigthrotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
			w[j] = w[j - 16] + sha256->s0 + w[j - 7] + sha256->s1;
			j++;
		}
		sha256->a = sha256->h_a[0];
		sha256->b = sha256->h_a[1];
		sha256->c = sha256->h_a[2];
		sha256->d = sha256->h_a[3];
		sha256->e = sha256->h_a[4];
		sha256->f = sha256->h_a[5];
		sha256->g = sha256->h_a[6];
		sha256->h = sha256->h_a[7];
		sha256_main_loop(w, sha256);
		sha256->h_a[0] += sha256->a;
		sha256->h_a[1] += sha256->b;
		sha256->h_a[2] += sha256->c;
		sha256->h_a[3] += sha256->d;
		sha256->h_a[4] += sha256->e;
		sha256->h_a[5] += sha256->f;
		sha256->h_a[6] += sha256->g;
		sha256->h_a[7] += sha256->h;
	}
}

unsigned char	*sha256(const unsigned char *d, size_t n, unsigned char *md)
{
	u_char		*message;
	t_sha256	sha256;
	int			i;

	sha256_init(&sha256);
	sha256.original_byte_len = n;
	sha256.original_bit_len = n * 8;
	sha256_message_preprocess(&message, d, &sha256);
	calculate_sha256_hash(message, &sha256);
	ft_memdel((void**)&message);
	if ((md = (unsigned char *)malloc(sizeof(unsigned char) * 32)) == NULL)
		return (NULL);
	i = -1;
	while (++i < 8)
		sha256.h_a[i] = reverse_order_word(sha256.h_a[i]);
	ft_memcpy(md, (void*)sha256.h_a, 32);
	return (md);
}
