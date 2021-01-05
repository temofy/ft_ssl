#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"

#define RESERVE_FOR_PADDING 64
#define SINGLE_BIT 128
#define SHA256_HASH_BIT 256

typedef struct	s_sha256
{
	size_t			original_bit_len;
	size_t			original_byte_len;
	size_t			variable_bit_len;
    uint32_t        h_a[8];
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
	//size_t			variable_byte_len;

	//t_hash_buffer	buffer;
}				t_sha256;


void   write_block_to_words(unsigned int *x, unsigned char *block);
unsigned char *sha256(const unsigned char *d, size_t n, unsigned char *md);