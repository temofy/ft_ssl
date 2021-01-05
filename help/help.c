#include "../libft/libft.h"

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

