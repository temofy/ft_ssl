/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:02:51 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:24:59 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

char	*get_command(t_command cmd)
{
	if (cmd == MD5_CMD)
		return ("md5");
	else if (cmd == SHA224_CMD)
		return ("sha224");
	else if (cmd == SHA256_CMD)
		return ("sha256");
	else if (cmd == SHA512_CMD)
		return ("sha512");
	return (NULL);
}

void	free_content(void *ptr, size_t content_size)
{
	content_size++;
	content_size = 0;
	free(ptr);
}

void	handle_s_string(t_ssl_args *ft_ssl_args)
{
	t_list	*head;
	t_msg	*message;

	head = ft_ssl_args->s_strings;
	while (ft_ssl_args->s_strings)
	{
		message = malloc(sizeof(t_msg));
		message->msg = (u_char*)ft_strdup((char*)
			ft_ssl_args->s_strings->content);
		message->msg_len = ft_ssl_args->s_strings->content_size;
		calculate_hash(message, ft_ssl_args);
		ft_ssl_args->s_strings = ft_ssl_args->s_strings->next;
	}
	ft_ssl_args->s_strings = head;
	ft_lstdel(&ft_ssl_args->s_strings, free_content);
}

void	handle_files(t_ssl_args *ft_ssl_args)
{
	t_list	*head;
	t_msg	*message;
	int		fd;

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
			ft_printf("ft_ssl: %s: %s: No such file or directory\n",
			get_command(ft_ssl_args->cmd), (char*)ft_ssl_args->files->content);
		ft_ssl_args->files = ft_ssl_args->files->next;
	}
	ft_ssl_args->files = head;
	ft_lstdel(&ft_ssl_args->files, free_content);
}
