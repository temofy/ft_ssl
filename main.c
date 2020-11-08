#include "include/ft_ssl.h"
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

char	*get_command(t_command cmd)
{
	if (cmd == MD5_CMD)
		return ("md5");
	else if (cmd == SHA256_CMD)
		return ("sha256");
	else if (cmd == SHA512_CMD)
		return ("sha512");
	return (NULL);
}

void	print_hash(unsigned char *hash, size_t hash_bit)
{
	for (int i=0;i< 16;i++)
	{
		printf("%02x", hash[i]);
	}
}

char	*read_input(int fd)
{
	char *message;
	char buf[50];
	size_t message_len = 0;
	size_t read_bytes;

	read_bytes = 0;
	message = NULL;
	bzero(buf, 50);
	while ((read_bytes = read(fd, buf, sizeof(buf))) > 0)
	{
		if (message == NULL)
			message = ft_strdup(buf);
		else
			message = ft_strfjoin(message, buf, 1);
		message_len += read_bytes;
		bzero(buf, read_bytes);
	}
	// ft_putstr("\nMessage: ");
	// ft_putstr(message);
	// ft_putstr("\n");
	return (message);
}

void	calculate_hash(char *message, t_ssl_args *ft_ssl_args)
{
	unsigned char	*hash;

	//if(ft_ssl_args->file != NULL)
		
	if (ft_ssl_args->cmd == MD5_CMD)
	{
		MD5(message, ft_strlen(message), hash);
		if (ft_ssl_args->file || (ft_ssl_args->flags && FLAG_S))
		{
			if (ft_ssl_args->flags && FLAG_R)
			{
				print_hash(hash, MD5_HASH_BIT);
				if (ft_ssl_args->file && ((ft_ssl_args->flags && FLAG_Q) == 0))
					printf(" %s\n", ft_ssl_args->file);
				else if ((ft_ssl_args->flags && FLAG_S) && ((ft_ssl_args->flags && FLAG_Q) == 0))
					printf(" (\"%s\"", message);
			}
			else
			{
				if (ft_ssl_args->file && ((ft_ssl_args->flags && FLAG_Q) == 0))
					printf("MD5 (%s) = ", ft_ssl_args->file);
				else if ((ft_ssl_args->flags && FLAG_S) && ((ft_ssl_args->flags && FLAG_Q) == 0)) 
					printf("MD5 (\"%s\" = ", message);
				print_hash(hash, MD5_HASH_BIT);
			}
		}
		else
			print_hash(hash, MD5_HASH_BIT);
	}
	else if (ft_ssl_args->cmd == SHA256_CMD)
	{

	}
	else if (ft_ssl_args->cmd == SHA512_CMD)
	{

	}
}

void	read_flags(int argc, char **argv, t_ssl_args *ft_ssl_args, int i_arg)
{
	ft_ssl_args->flags = 0;

	while (i_arg < argc && argv[i_arg][0] == '-')
	{
		int i;
		size_t arg_len;

		i = 1;
		arg_len = ft_strlen(argv[i_arg]);
		while (i < arg_len)
		{
			if (ft_strchr("pqrs", argv[i_arg][i]))
			{
				if (argv[i_arg][i] == 'p')
				{
					char	*message;

					ft_ssl_args->flags |= FLAG_P;
					message = read_input(0);
					printf("%s\n", message);
					calculate_hash(message, ft_ssl_args);
				}
				else if (argv[i_arg][i] == 'q')
				{
					ft_ssl_args->flags |= FLAG_Q;
				}
				else if (argv[i_arg][i] == 'r')
				{
					ft_ssl_args->flags |= FLAG_R;
				}
				else if (argv[i_arg][i] == 's')
				{
					ft_ssl_args->flags |= FLAG_S;
					if (i_arg + 1 < argc)
					{
						calculate_hash(argv[++i_arg], ft_ssl_args);
					}
					else
					{
						//error
					}
				}
			}
			else
			{
				//error 
			}
			i++;
		} 
		i_arg++;
	}
}

unsigned char	*read_file(int argc, char **argv, t_ssl_args *ft_ssl_args, int i_arg)
{
	unsigned char	*message;
	int				fd;
	
	while (i_arg < argc)
	{
		if (fd = open("file", O_RDONLY) != -1)
		{
			printf("fd: %i\n", fd);
			//message = read_input(fd);
			//calculate_hash(message, ft_ssl_args);
			//close(fd);
		}
		else
		{
			printf("ft_ssl: %s: %s: No such file or directory", get_command(ft_ssl_args->cmd), argv[i_arg]);
			//ft_ssl: md5: -s: No such file or directory
			//error file
		}
		i_arg++;
	}
}

void	read_args(int argc, char **argv, t_ssl_args *ft_ssl_args)
{
	int i_arg;

	i_arg = 2;
	ft_ssl_args->file = NULL;
	if (argc <= 1)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]");
		exit(1);
	}
	if (!ft_strcmp(argv[1], "md5"))
		ft_ssl_args->cmd = MD5_CMD;
	else if (!ft_strcmp(argv[1], "sha256"))
		ft_ssl_args->cmd = SHA256_CMD;
	else if (!ft_strcmp(argv[1], "sha512"))
		ft_ssl_args->cmd = SHA512_CMD;
	else
	{
		printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
		ft_putstr("\nStandard commands:\n\nMessage Digest commands:\n");
		ft_putstr("md5\nsha256\nsha512\n\nCipher commands:\n");
		exit(1);
	}
	read_flags(argc, argv, ft_ssl_args, i_arg);
	read_file(argc, argv, ft_ssl_args, i_arg);	
}

int main(int argc, char **argv)
{
	unsigned char *md;
	t_ssl_args ft_ssl_args;


	md = NULL;
	read_args(argc, argv, &ft_ssl_args);
	return (0);
}