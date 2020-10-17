//#include "md5.h"
#include <stdlib.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"

char *convert_str_to_hex(unsigned char *str)
{
	int		i;
	int		j;
	size_t	len;
	unsigned char	*hex_str;
	char *tmp;

	i = -1;
	j = -1;
	len = strlen(str); 
	hex_str = (unsigned char*)malloc(sizeof(unsigned char) * len * 2);
	while (++j < 32)
		hex_str[j] = '0';
	j = -1;
	while (++i < len)
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

int main (int argc, char **argv)
{
	unsigned char *name = "ffsafafafafafff";
	unsigned char *digest;
	unsigned char *digest2;

	digest = (char*)malloc(sizeof(char) * 16);
	MD5(name, strlen(name), digest);
	printf("Digest: %s | address: %p\n", convert_str_to_hex(digest), digest);
	for (int i=0;i<MD5_DIGEST_LENGTH;i++) {
		ft_printf("%02x\n",digest[i]);
    };


}