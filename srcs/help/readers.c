/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:50 by cheller           #+#    #+#             */
/*   Updated: 2021/01/08 10:41:08 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

t_msg	*read_input(int fd)
{
	char	*buf;
	size_t	read_bytes;
	t_msg	*message;

	message = (t_msg*)malloc(sizeof(t_msg));
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

void	parse_flags(t_p_args *p_args, t_ssl_args *args, int *i_arg, size_t *i)
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

void	read_flags(int argc, char **argv, t_ssl_args *ft_ssl_args, int *i_arg)
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
				parse_flags(&p_args, ft_ssl_args, i_arg, &i);
			else
			{
				ft_printf("ft_ssl: invalid option -- '%c'\n", argv[*i_arg][i]);
				ft_lstdel(&ft_ssl_args->s_strings, free_content);
				exit(1);
			}
			i++;
		}
		(*i_arg)++;
	}
}

void	read_files(int argc, char **argv, t_ssl_args *ft_ssl_args, int *i_arg)
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

void	read_args(int argc, char **argv, t_ssl_args *ft_ssl_args)
{
	int	i_arg;

	i_arg = 2;
	if (argc <= 1)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
		exit(1);
	}
	if (!ft_strcmp(argv[1], "md5"))
		ft_ssl_args->cmd = MD5_CMD;
	else if (!ft_strcmp(argv[1], "sha224"))
		ft_ssl_args->cmd = SHA224_CMD;
	else if (!ft_strcmp(argv[1], "sha256"))
		ft_ssl_args->cmd = SHA256_CMD;
	else if (!ft_strcmp(argv[1], "sha512"))
		ft_ssl_args->cmd = SHA512_CMD;
	else
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
		ft_putstr("\nStandard commands:\n\nMessage Digest commands:\n");
		ft_putstr("md5\nsha224\nsha256\nsha512\n\nCipher commands:\n");
		exit(1);
	}
	read_flags(argc, argv, ft_ssl_args, &i_arg);
	read_files(argc, argv, ft_ssl_args, &i_arg);
}
