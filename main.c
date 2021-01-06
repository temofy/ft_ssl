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

void		print_hash(unsigned char *hash, size_t hash_bit)
{
	size_t	i;

	i = -1;
	while (++i < hash_bit / 8)
	{
		printf("%02x", hash[i]);
	}
}

t_message	*read_input(int fd)
{
	char		*buf;
	size_t		read_bytes;
	t_message	*message;

	message = (t_message*)malloc(sizeof(t_message));
	read_bytes = 0;
	message->msg = NULL;
	message->msg_len = 0;
	buf = ft_memalloc(BUFF_SIZE);
	while ((read_bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (message->msg == NULL)
		{
			message->msg = ft_memalloc(read_bytes);
			message->msg = ft_memcpy(message->msg, buf, read_bytes);
			ft_strdel(&buf);
		}
		else
			message->msg = (u_char*)ft_strljoin((char*)message->msg, buf,
				message->msg_len, read_bytes);
		message->msg_len += read_bytes;
		buf = ft_memalloc(BUFF_SIZE);
	}
	ft_strdel(&buf);
	return (message);
}

void		handle_md5_cmd(t_message *message, t_ssl_args *ft_ssl_args)
{
	unsigned char	*hash;

	hash = NULL;
	if ((hash = MD5(message->msg, message->msg_len, hash)) == NULL)
		return ;
	if (ft_ssl_args->flags & FLAG_P)
	{
		printf("%s", message->msg);
		ft_ssl_args->flags -= FLAG_P; 
		print_hash(hash, MD5_HASH_BIT);
	}
	else if (ft_ssl_args->files || (ft_ssl_args->flags & FLAG_S))
	{
		if (ft_ssl_args->flags & FLAG_R)
		{
			print_hash(hash, MD5_HASH_BIT);
			if ((ft_ssl_args->flags & FLAG_S)  && ft_ssl_args->s_strings && ((ft_ssl_args->flags & FLAG_Q) == 0))
				printf(" \"%s\"", message->msg);
			else if (ft_ssl_args->files && ((ft_ssl_args->flags & FLAG_Q) == 0))
				printf(" %s", (char*)ft_ssl_args->files->content);
		}
		else
		{
			if ((ft_ssl_args->flags & FLAG_S) && ft_ssl_args->s_strings && ((ft_ssl_args->flags & FLAG_Q) == 0)) 
				printf("MD5 (\"%s\") = ", message->msg);
			else if (ft_ssl_args->files && ((ft_ssl_args->flags & FLAG_Q) == 0))
				printf("MD5 (%s) = ", (char*)ft_ssl_args->files->content);
			print_hash(hash, MD5_HASH_BIT);
		}
	}
	else
		print_hash(hash, MD5_HASH_BIT);
	ft_memdel((void**)&hash);
}

// void		handle_sha224_cmd(t_message *message, t_ssl_args *ft_ssl_args)
// {

// }

void		handle_sha256_cmd(t_message *message, t_ssl_args *ft_ssl_args)
{
	unsigned char	*hash;

	hash = NULL;
	if ((hash = sha256(message->msg, message->msg_len, hash)) == NULL)
		return ;
	if (ft_ssl_args->flags & FLAG_P)
	{
		printf("%s", message->msg);
		ft_ssl_args->flags -= FLAG_P; 
		print_hash(hash, SHA256_HASH_BIT);
	}
	else if (ft_ssl_args->files || (ft_ssl_args->flags & FLAG_S))
	{
		if (ft_ssl_args->flags & FLAG_R)
		{
			print_hash(hash, SHA256_HASH_BIT);
			if ((ft_ssl_args->flags & FLAG_S)  && ft_ssl_args->s_strings && ((ft_ssl_args->flags & FLAG_Q) == 0))
				printf(" \"%s\"", message->msg);
			else if (ft_ssl_args->files && ((ft_ssl_args->flags & FLAG_Q) == 0))
				printf(" %s", (char*)ft_ssl_args->files->content);
		}
		else
		{
			if ((ft_ssl_args->flags & FLAG_S) && ft_ssl_args->s_strings && ((ft_ssl_args->flags & FLAG_Q) == 0)) 
				printf("SHA256 (\"%s\") = ", message->msg);
			else if (ft_ssl_args->files && ((ft_ssl_args->flags & FLAG_Q) == 0))
				printf("SHA256 (%s) = ", (char*)ft_ssl_args->files->content);
			print_hash(hash, SHA256_HASH_BIT);
		}
	}
	else
		print_hash(hash, SHA256_HASH_BIT);
	ft_memdel((void**)&hash);
}

void		calculate_hash(t_message *message, t_ssl_args *ft_ssl_args)
{		
	if (ft_ssl_args->cmd == MD5_CMD)
	{
		handle_md5_cmd(message, ft_ssl_args);
	}
	else if (ft_ssl_args->cmd == SHA224_CMD)
	{
		//handle_sha224_cmd(message, ft_ssl_args);
	}
	else if (ft_ssl_args->cmd == SHA256_CMD)
	{
		handle_sha256_cmd(message, ft_ssl_args);
	}
	else if (ft_ssl_args->cmd == SHA512_CMD)
	{

	}
	ft_memdel((void**)&message->msg);
	ft_memdel((void**)&message);
	printf("\n");
}

void	handle_flags(t_p_args *p_args, t_ssl_args *args, int *i_arg, size_t *i)
{
	if (p_args->argv[*i_arg][*i] == 'p')
		args->flags |= FLAG_P;
	else if (p_args->argv[*i_arg][*i] == 'q')
		args->flags |= FLAG_Q;
	else if (p_args->argv[*i_arg][*i] == 'r')
		args->flags |= FLAG_R;
	else if (p_args->argv[*i_arg][*i] == 's')
	{
		args->flags |= FLAG_S;
		if (*i_arg + 1 < p_args->argc)
		{
			if (!args->s_strings)
				args->s_strings = ft_lstnew(p_args->argv[*i_arg + 1],
					ft_strlen(p_args->argv[*i_arg + 1]));
			else
				ft_lstappend(&args->s_strings,
					ft_lstnew(p_args->argv[*i_arg + 1],
						ft_strlen(p_args->argv[*i_arg + 1])));
			(*i_arg)++;
		}
	}
}

void		read_flags(int argc, char **argv, t_ssl_args *ft_ssl_args, int *i_arg)
{
	size_t		i;
	size_t		arg_len;
	t_p_args	p_args;

	p_args.argc = argc;
	p_args.argv = argv;
	ft_ssl_args->flags = 0;
	while (*i_arg < argc && argv[*i_arg][0] == '-')
	{
		i = 1;
		arg_len = ft_strlen(argv[*i_arg]);
		while (i < arg_len)
		{
			if (ft_strchr("pqrs", argv[*i_arg][i]))
			{
				handle_flags(&p_args, ft_ssl_args, i_arg, &i);
			}
			else
				return ;
			i++;
		}
		(*i_arg)++;
	}
}

void		read_files(int argc, char **argv, t_ssl_args *ft_ssl_args, int *i_arg)
{
	while (*i_arg < argc)
	{
		if (!ft_ssl_args->files)
			ft_ssl_args->files = ft_lstnew(argv[*i_arg],
				ft_strlen(argv[*i_arg]));
		else
			ft_lstappend(&ft_ssl_args->files, ft_lstnew(argv[*i_arg],
				ft_strlen(argv[*i_arg])));
		(*i_arg)++;
	}
}

void		read_args(int argc, char **argv, t_ssl_args *ft_ssl_args)
{
	int i_arg;

	i_arg = 2;
	ft_ssl_args->s_strings = NULL;
	ft_ssl_args->files = NULL;
	if (argc <= 1)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
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
		ft_putstr("md5\nsha224\nsha256\nsha512\n\nCipher commands:\n");
		exit(1);
	}
	read_flags(argc, argv, ft_ssl_args, &i_arg);
	read_files(argc, argv, ft_ssl_args, &i_arg);
}

void		free_content(void *ptr, size_t content_size)
{
	content_size++;
	content_size = 0;
	free(ptr);
}

void		handle_s_string(t_ssl_args *ft_ssl_args)
{
	t_list		*head;
	t_message	*message;

	head = ft_ssl_args->s_strings;
	while (ft_ssl_args->s_strings)
	{
		message = malloc(sizeof(t_message));
		message->msg = (u_char*)ft_strdup((char*)
			ft_ssl_args->s_strings->content);
		message->msg_len = ft_ssl_args->s_strings->content_size;
		calculate_hash(message, ft_ssl_args);
		ft_ssl_args->s_strings = ft_ssl_args->s_strings->next;
	}
	ft_ssl_args->s_strings = head;
	ft_lstdel(&ft_ssl_args->s_strings, free_content);
}

void		handle_files(t_ssl_args *ft_ssl_args)
{
	t_list		*head;
	t_message	*message;
	int			fd;

	head = ft_ssl_args->files;
	while (ft_ssl_args->files)
	{
		if ((fd = open(ft_ssl_args->files->content, O_RDONLY)) != -1)
		{
			message = read_input(fd);
			calculate_hash(message, ft_ssl_args);
			close(fd);
		}
		else
			printf("ft_ssl: %s: %s: No such file or directory\n",
			get_command(ft_ssl_args->cmd), (char*)ft_ssl_args->files->content);
		ft_ssl_args->files = ft_ssl_args->files->next;
	}
	ft_ssl_args->files = head;
	ft_lstdel(&ft_ssl_args->files, free_content);
}

int			main(int argc, char **argv)
{
	t_message	*message;
	t_ssl_args	ft_ssl_args;

	message = NULL;
	read_args(argc, argv, &ft_ssl_args);
	if (ft_ssl_args.flags & FLAG_P || (!ft_ssl_args.files &&
		!(ft_ssl_args.flags & FLAG_S)))
	{
		message = read_input(0);
		calculate_hash(message, &ft_ssl_args);
	}
	handle_s_string(&ft_ssl_args);
	handle_files(&ft_ssl_args);
	return (0);
}
