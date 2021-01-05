#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

#define DWORD unsigned int
#define RESERVE_FOR_PADDING 64
#define SINGLE_BIT 128
#define MD5_HASH_BIT 128

typedef struct s_hash_buffer
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
	//size_t			variable_byte_len;

	t_hash_buffer	buffer;
}				t_md5;		

unsigned char	*MD5(const unsigned char *d, unsigned long n, unsigned char *md);
void			write_block_to_words(unsigned int *x, unsigned char *block);
