#include "../include/md5.h"

const unsigned int s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, // добавить префикс скорее всего
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

const unsigned int g_k_md5[] = {0xd76aa478, 0xe8c7b756, 0x242070db,
	0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
	0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
	0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,
	0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87,
	0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942,
	0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
	0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039,
	0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7,
	0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f,
	0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
	0xeb86d391};

unsigned char *split_by_byte(unsigned long var, size_t size)
{
	unsigned char *splitted_var;
	int i;
	int j;

	i = size;
	j = 0;
	splitted_var = (unsigned char*)malloc(sizeof(unsigned char) * size);
	ft_bzero(splitted_var, size);
	while (--i >= 0)
	{
		splitted_var[j++] |= (unsigned char) (var >> (8 * i));
	}
	return (splitted_var);
}

void adding_message_length(unsigned char *message, t_md5 *md5)
{
	message += md5->variable_bit_len / 8;
	ft_memcpy((void*)message, &md5->original_bit_len, 8);
	md5->variable_bit_len += 64;
}

unsigned int fun_f(unsigned int b, unsigned int c, unsigned int d)
{
	return ((b & c) | (~b & d));
}

unsigned int fun_g(unsigned int b, unsigned int c, unsigned int d)
{
	return ((b & d) | (c & ~d));
}

unsigned int fun_h(unsigned int b, unsigned int c, unsigned int d)
{
	return (b ^ c ^ d);
}

unsigned int fun_i(unsigned int b, unsigned int c, unsigned int d)
{
	return (c ^ (b | ~d));
}


char		*add0(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i < 8)
	{
		ft_putchar('0');
		i++;
	}
	return (str);
}


void		print_md5_digest(t_hash_buffer *buffer)
{
	char	*tmp;

	tmp = ft_unsigned_itoa_base(buffer->a, 16);
	add0(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_unsigned_itoa_base(buffer->b, 16);
	add0(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_unsigned_itoa_base(buffer->c, 16);
	add0(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_unsigned_itoa_base(buffer->d, 16);
	add0(tmp);
	ft_putstr(tmp);
	free(tmp);
}

void calculate_md5_hash(unsigned char *message, t_md5 *md5)
{
	DWORD	a;
	DWORD	b;
	DWORD	c;
	DWORD	d;
	size_t	i;
	size_t	chunks_number;

	a = 0x67452301;
	b = 0xefcdab89;
	c = 0x98badcfe;
	d = 0x10325476;

	i = -1;
	chunks_number = md5->variable_bit_len / 512;
	while (++i < chunks_number) 
	{
		int j = -1;
		unsigned int k = 0;
		unsigned int f;
		unsigned int x[16];

		unsigned int aa = a;
		unsigned int bb = b;
		unsigned int cc = c;
		unsigned int dd = d;

		write_block_to_words(x, message + 64 * i);
		while (++j < 64)
		{  
			if (j >= 0 && j <= 15)
			{
				f = fun_f(bb, cc, dd);
				k = j;
			}
			else if (j >= 16 && j <= 31)
			{
				f = fun_g(bb, cc, dd);
				k = (5 * j + 1) % 16;
			}
			else if (j >= 32 && j <= 47)
			{
				f = fun_h(bb, cc, dd);
				k = (3 * j + 5) % 16;
			}
			else if (j >= 48 && j <= 63)
			{
				f = fun_i(bb, cc, dd);
				k = (7 * j) % 16;
			}
			f = f + aa + g_k_md5[j] + x[k];
			aa = dd;
			dd = cc;
			cc = bb;
			bb = bb + leftrotate(f, s[j]);
		}
		
		a = a + aa;
		b = b + bb;
		c = c + cc;
		d = d + dd;

		md5->buffer.a = a;
		md5->buffer.b = b;
		md5->buffer.c = c;
		md5->buffer.d = d;
	}
}

void md5_message_preprocess(unsigned char **message, const unsigned char *original_message, t_md5 *md5)
{
	size_t	i;

	*message = (unsigned char*)malloc(sizeof(unsigned char) * (md5->original_byte_len + RESERVE_FOR_PADDING));
	ft_bzero((*message) + md5->original_byte_len, sizeof(unsigned char) * (RESERVE_FOR_PADDING));

	i = -1;
	while (++i < md5->original_byte_len)
	{
		(*message)[i] = original_message[i];
	}
	(*message)[i] = SINGLE_BIT;

	md5->variable_bit_len = md5->original_bit_len;
	md5->variable_bit_len++;

	while (1)
	{
		if (md5->variable_bit_len % 512 == 448)
			break;
		md5->variable_bit_len++;
	}
}

unsigned char *MD5(const unsigned char *d, unsigned long n, unsigned char *md)
{
	u_char	*message;
	t_md5	md5;
	int		i;	
	int		j;

	i = 0;
	md5.original_byte_len = n;
	md5.original_bit_len = n * 8;
	md5_message_preprocess(&message, d, &md5);
	adding_message_length(message, &md5);
	calculate_md5_hash(message, &md5);
	ft_memdel((void**)&message);
	md = (unsigned char *)malloc(sizeof(unsigned char) * 16);
	j = -1;
	while (++j < 4)
		md[i++] = ((unsigned char *)&md5.buffer.a)[j];
	j = -1;
	while (++j < 4)
		md[i++] = ((unsigned char *)&md5.buffer.b)[j];
	j = -1;
	while (++j < 4)
		md[i++] = ((unsigned char *)&md5.buffer.c)[j];
	j = -1;
	while (++j < 4)
		md[i++] = ((unsigned char *)&md5.buffer.d)[j];	
	return (md);
}