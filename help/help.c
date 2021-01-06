#include "../libft/libft.h"
#include <stdint.h>

void   write_block_to_words(unsigned int *x, unsigned char *block)
{
	int			i;
	int			size;

	i = 0;
	size = 0;
	while (i < 16)
	{
		ft_memcpy(&x[i], (block + size), 4);
		size += 4;
		i++;
	}
}

unsigned int leftrotate(unsigned int f, unsigned int s0)
{
	return (((f) << (s0)) | ((f) >> (32 - (s0))));
}

uint32_t	rigthrotate(uint32_t x, uint32_t n)
{
	return ((((unsigned int)x >> n)) | (x << (32 - n)));
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
