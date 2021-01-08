/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:03:01 by cheller           #+#    #+#             */
/*   Updated: 2021/01/08 18:31:21 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "md5.h"
# include "sha.h"
# include <fcntl.h>

# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8

typedef enum	e_command
{
	MD5_CMD,
	SHA224_CMD,
	SHA256_CMD,
	SHA512_CMD
}				t_command;

typedef struct	s_message
{
	u_char		*msg;
	size_t		msg_len;
}				t_msg;

typedef struct	s_program_args
{
	char		**argv;
	int			argc;
}				t_p_args;

typedef struct	s_ssl_args
{
	t_command	cmd;
	uint		flags;
	t_list		*s_strings;
	t_list		*files;
}				t_ssl_args;

char			*convert_hash_to_str(u_char *hash, int bit_hash);
t_msg			*read_input(int fd);
char			*get_command(t_command cmd);
void			free_content(void *ptr, size_t content_size);
void			read_args(int argc, char **argv, t_ssl_args *ft_ssl_args);
void			calculate_hash(t_msg *message, t_ssl_args *ft_ssl_args);
void			handle_s_string(t_ssl_args *ft_ssl_args);
void			handle_files(t_ssl_args *ft_ssl_args);

#endif
