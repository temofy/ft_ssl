#include "include/md5.h"
#include <stdio.h> // удалить

unsigned char *convert_str_to_hex(unsigned char *str) // всё правильно, изменено на unsigned
{
	int		i;
	int		j;
	size_t	len;
	unsigned char	*hex_str;
	char *tmp;

	i = -1;
	j = -1;
	len = strlen((char*)str); 
	hex_str = (unsigned char*)malloc(sizeof(unsigned char) * len * 2);
	while (++j < 32)
		hex_str[j] = '0';
	j = -1;
	while (++i < (long int)len)
	{
		//printf("Hex: %s\n", ft_itoa_base(str[i], 16));
		tmp = ft_itoa_base(str[i], 16);
		if (ft_strlen(tmp) == 2)
		{
			hex_str[++j] = ft_tolower(tmp[0]);
			hex_str[++j] = ft_tolower(tmp[1]);
		}
		else
		{
			++j;
			hex_str[++j] = tmp[0];
		}
		free(tmp);
	}
	return (hex_str);
}

int main(int argc, char **argv)
{
	//unsigned char str[] = "Artem";
	unsigned char *md;

	md = NULL;
	if (argc > 1)
	{
		size_t len = strlen(argv[1]);

		MD5((unsigned char*)argv[1], len, md);
		printf("Digest: ");
		for (int i=0;i< 16;i++)
		{
			printf("%02x", md[i]);
		};
		printf("\n");
	}
	return (0);
}