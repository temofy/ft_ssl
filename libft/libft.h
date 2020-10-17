/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temofy <temofy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:01:24 by cheller           #+#    #+#             */
/*   Updated: 2020/09/10 00:10:49 by temofy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define BUFF_SIZE 1
# define MAX_I 214748364

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_lst_fd
{
	int				fd;
	char			*tmp_line;
	struct s_lst_fd	*next_lst;
}					t_list_fd;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *hys, const char *need);
char				*ft_strnstr(const char *hys, const char *need, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list*(*f)(t_list *elem));

char				*ft_strtchr(char *s, int c);
char				*ft_strrev(char *str);
char				*ft_litoa(long long int n);
char				*ft_uitoa(unsigned n);
char				*ft_ulitoa(unsigned long long int n);
char				*ft_strftchr(char *s, int pos, int c);
int					ft_isthere_chr(char *s, int c);
char				*ft_strfjoin(char *s1, char *s2, int arg_to_free);
char				*ft_strljoin(char *s1, char *s2, int len1, int len2);
char				*ft_strnew_set(char c, size_t size);
int					ft_abs(int n);
int					ft_iseven(long nbr);
char				*ft_itoa_base(int value, int base);
char				*ft_unsigned_itoa_base(unsigned int value, int base);
size_t				ft_intlen(const unsigned int *nbr);
long				ft_atoi_f(const char *s, int *flag);
int					ft_strposchr(char *s, int c);
int					get_next_line(const int fd, char **line);
int					ft_arraylen(void **array);
void				ft_arrdel(char ***arr);
int					ft_count_words(char *str);
int					ft_isthere_str(char *str, char *substr);
t_list_fd			*ft_lstnew_fd(int fd, char *tmp);
t_list_fd			*ft_find_last_lst(t_list_fd *first_lst);
int					ft_nbrlen(int n);
int					ft_str_isempty(char *str);
char				**ft_strmatrix(int m, int n);
size_t				ft_strclen(const char *s, int c);
#endif
