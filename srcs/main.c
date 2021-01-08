/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:02:29 by cheller           #+#    #+#             */
/*   Updated: 2021/01/08 18:43:46 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

void	print_hash(unsigned char *hash, t_command cmd)
{
	size_t	hash_bit;
	char	*hash_str;

	if (cmd == MD5_CMD)
		hash_bit = MD5_HASH_BIT;
	else if (cmd == SHA224_CMD)
		hash_bit = SHA224_HASH_BIT;
	else if (cmd == SHA256_CMD)
		hash_bit = SHA256_HASH_BIT;
	else if (cmd == SHA512_CMD)
		hash_bit = SHA512_HASH_BIT;
	hash_str = convert_hash_to_str(hash, hash_bit);
	ft_printf("%s", hash_str);
	ft_memdel((void**)&hash_str);
}

void	print_hash_with_files_flags(t_msg *msg, t_ssl_args *args, u_char *hash)
{
	char	*cmd;

	cmd = ft_str_toupper(ft_strdup(get_command(args->cmd)));
	if (args->flags & FLAG_R)
	{
		print_hash(hash, args->cmd);
		if ((args->flags & FLAG_S) && args->s_strings
				&& ((args->flags & FLAG_Q) == 0))
			ft_printf(" \"%s\"", msg->msg);
		else if (args->files && ((args->flags & FLAG_Q) == 0))
			ft_printf(" %s", (char*)args->files->content);
	}
	else
	{
		if ((args->flags & FLAG_S) && args->s_strings
				&& ((args->flags & FLAG_Q) == 0))
			ft_printf("%s (\"%s\") = ", cmd, msg->msg);
		else if (args->files && ((args->flags & FLAG_Q) == 0))
			ft_printf("%s (%s) = ", cmd, (char*)args->files->content);
		print_hash(hash, args->cmd);
	}
	ft_strdel(&cmd);
}

void	handle_flags(t_msg *message, t_ssl_args *ft_ssl_args, u_char *hash)
{
	if (ft_ssl_args->flags & FLAG_P)
	{
		ft_printf("%s", message->msg);
		ft_ssl_args->flags -= FLAG_P;
		print_hash(hash, ft_ssl_args->cmd);
	}
	else if (ft_ssl_args->files || (ft_ssl_args->flags & FLAG_S))
	{
		print_hash_with_files_flags(message, ft_ssl_args, hash);
	}
	else
		print_hash(hash, ft_ssl_args->cmd);
}

void	calculate_hash(t_msg *message, t_ssl_args *ft_ssl_args)
{
	u_char	*hash;

	hash = NULL;
	if (ft_ssl_args->cmd == MD5_CMD)
		hash = md5(message->msg, message->msg_len, hash);
	else if (ft_ssl_args->cmd == SHA224_CMD)
		hash = sha224(message->msg, message->msg_len, hash);
	else if (ft_ssl_args->cmd == SHA256_CMD)
		hash = sha256(message->msg, message->msg_len, hash);
	else if (ft_ssl_args->cmd == SHA512_CMD)
		hash = sha512(message->msg, message->msg_len, hash);
	if (hash == NULL)
		return ;
	handle_flags(message, ft_ssl_args, hash);
	ft_memdel((void**)&hash);
	ft_memdel((void**)&message->msg);
	ft_memdel((void**)&message);
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	t_msg		*message;
	t_ssl_args	ft_ssl_args;

	message = NULL;
	ft_ssl_args.s_strings = NULL;
	ft_ssl_args.files = NULL;
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
