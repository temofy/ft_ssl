#include "../include/md5.h"

#include <math.h> // удалить и заменить констатной переменной

const unsigned int s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};


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

void adding_message_length(unsigned char *stream, size_t *len_bits, size_t *len_bytes)
{
	unsigned int low_bytes = 0;
	unsigned int high_bytes = 0;
	int i;

	unsigned int bit;

	i = 32;

	while (--i >= 0)
	{
		bit = *len_bits >> i & 1;
		low_bytes += bit << i;
	}

	i = 64;

	while (--i >= 32)
	{
		bit = *len_bits >> i & 1;
		high_bytes += bit << i;
	}

	unsigned char *splitted_var; 

	// low_bytes = 34508;
	// uc |= (unsigned char) (low_bytes);
	// uc = 0;
	// uc |= (unsigned char) (low_bytes >> 8);
	i  = -1;
	splitted_var = split_by_byte((unsigned long)low_bytes, sizeof(low_bytes));
	while (++i < 4)
	{
		stream[(*len_bytes)++] = splitted_var[i];
	}
	free(splitted_var);

	i  = -1;
	splitted_var = split_by_byte((unsigned long)high_bytes, sizeof(high_bytes));
	while (++i < 4)
	{
		stream[(*len_bytes)++] = splitted_var[i];
	}
	free(splitted_var);
}

int fun_f(int b, int c, int d)
{
	return ((b & c) | (~b & d));
}

int fun_g(int b, int c, int d)
{
	return ((b & c) | (b & ~d));
}

int fun_h(int b, int c, int d)
{
	return (b ^ c ^ d);
}

int fun_i(int b, int c, int d)
{
	return (b ^ (b | ~d));
}

void write_block_to_words(unsigned int *x, unsigned char *block)
{
	int i;
	int j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 4)
		{
			x[i] = block[i * 4 + j];
		}
	}
}

unsigned int leftrotate(unsigned int f, unsigned int s0)
{
	return (((f) << (s0)) | ((f) >> (32 - (s0))));
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

void calculate(unsigned char *stream, t_hash_buffer *buffer, size_t *len_bits, size_t *len_bytes)
{
	DWORD a;
	DWORD b;
	DWORD c;
	DWORD d;
	int t[64];
	int i;

	i = -1;
	while (++i < 64)
    	t[i] = (int)(4294967296 * ft_abs(sin(i + 1)));
	// for i from 0 to 63 do
    // 	K[i] := floor(232 × abs (sin(i + 1)))

	a = 19088743;
	b =  2309737967;
	c = 4275878552;
	d = 1985229328;

	i = -1;
	while (++i < (*len_bits) % 512) // разобраться тут
	{
		int j = -1;
		int k = 0;
		int f;
		unsigned int x[16];

		int aa = a;
		int bb = b;
		int cc = c;
		int dd = d;

		write_block_to_words(x, stream);
		while (++j < 64)
		{  
			if (j >= 0 && j <= 15)
			{
				f = fun_f(b, c, d);
				k = j;
			}
			else if (j >= 16 && j <= 31)
			{
				f = fun_g(b, c, d);
				k = (5 * j + 1) % 16;
			}
			else if (j >= 32 && j <= 47)
			{
				f = fun_h(b, c, d);
				k = (3 * j + 5) % 16;
			}
			else if (j >= 48 && j <= 63)
			{
				f = fun_i(b, c, d);
				k = (7 * j) % 16;
			}
			f = f + a + t[j] + x[k];
			aa = dd;
			bb = cc;
			cc = bb;
			bb = bb + leftrotate(f, s[j]);
		}
		
		a = a + aa;
		b = b + bb;
		c = c + cc;
		d = d + dd;

		buffer->a = a;
		buffer->b = b;
		buffer->c = c;
		buffer->d = d;
	}
	// После окончания цикла необходимо проверить, есть ли ещё блоки для вычислений. Если да, то переходим к следующему элементу массива (n + 1) и повторяем цикл.
	// Process the message in successive 512-bit chunks:
// for each 512-bit chunk of padded message do
//     break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15
//     // Initialize hash value for this chunk:
//     var int A := a0
//     var int B := b0
//     var int C := c0
//     var int D := d0
//     // Main loop:
//     for i from 0 to 63 do
//         var int F, g
//         if 0 ≤ i ≤ 15 then
//             F := (B and C) or ((not B) and D)
//             g := i
//         else if 16 ≤ i ≤ 31 then
//             F := (D and B) or ((not D) and C)
//             g := (5×i + 1) mod 16
//         else if 32 ≤ i ≤ 47 then
//             F := B xor C xor D
//             g := (3×i + 5) mod 16
//         else if 48 ≤ i ≤ 63 then
//             F := C xor (B or (not D))
//             g := (7×i) mod 16
//         // Be wary of the below definitions of a,b,c,d
//         F := F + A + K[i] + M[g]  // M[g] must be a 32-bits block
//         A := D
//         D := C
//         C := B
//         B := B + leftrotate(F, s[i])
//     end for
//     // Add this chunk's hash to result so far:
//     a0 := a0 + A
//     b0 := b0 + B
//     c0 := c0 + C
//     d0 := d0 + D
// end for

}

unsigned char *MD5(const unsigned char *d, unsigned long n, unsigned char *md)
{

	size_t len_bits;
	size_t len_bytes;
	t_hash_buffer	buffer;
	unsigned char *stream;
	int	i;

	// buffer.a = 19088743;
	// buffer.b = 2309737967;
	// buffer.c = 4275878552;
	// buffer.d = 1985229328;

	i = -1;
	len_bytes = ft_strlen(d); // проверить не нужен ли подсчет всех символов в диапозоне 0 до 255
								// подумать если длина сообщения превышает 2305843009213693952 байт
	len_bits = ft_strlen(d) * 8;  
	stream = (unsigned char*)malloc(sizeof(unsigned char) * (len_bytes + 64));\
	stream[sizeof(unsigned char) * (len_bytes + 64)] = 0;
	ft_bzero(stream, ft_strlen(stream));
	while (++i < len_bytes)
	{
		stream[i] = d[i];
	}
	stream[i] = 128;
	len_bits++;

	i = -1;
	printf("len_bits: %zu\n", len_bits);
	while (1)
	{
		if (len_bits % 512 == 448)
			break;
		len_bits++;
	}
	printf("len_bits: %zu\n", len_bits);

	len_bytes = len_bits / 8;
	adding_message_length(stream, &len_bits, &len_bytes);
	calculate(stream, &buffer, &len_bits, len_bytes);
	print_md5_digest(&buffer);
	//printf("Size: %zu\n", sizeof(a));
}