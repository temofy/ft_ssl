#ifndef FT_SSL_H
# define FT_SSL_H

# include "md5.h"
# include <fcntl.h>

# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8	

typedef enum	e_command
{
	MD5_CMD,
	SHA256_CMD,
	SHA512_CMD
}				t_command;

typedef struct	s_ssl_args
{
	t_command	cmd;
	uint		flags;
	char		*file;
}				t_ssl_args;

#endif
