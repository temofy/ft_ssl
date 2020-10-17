#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

#define DWORD unsigned long int

typedef struct s_hash_buffer
{
	DWORD	a;
	DWORD	b;
	DWORD	c;
	DWORD	d;
}				t_hash_buffer;

unsigned char *MD5(const unsigned char *d, unsigned long n, unsigned char *md);
