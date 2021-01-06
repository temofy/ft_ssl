#ifndef FT_SSL_H
# define FT_SSL_H

# include "md5.h"
# include "sha256.h"
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
}				t_message; 

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
	//unsigned char	**files;
}				t_ssl_args;

#endif
