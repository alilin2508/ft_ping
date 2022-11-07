/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:14:22 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/09 12:28:39 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# define _NC "\033[00m"
# define _RED "\033[0;31m"
# define _GREEN "\033[0;32m"
# define _YELLOW "\033[0;33m"
# define _BLUE "\033[0;34m"
# define _PURPLE "\033[0;95m"
# define _CYAN "\033[0;36m"
# define _WHITE "\033[0;37m"

# define TRUE 1
# define FALSE 0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void		ft_del_line(char *line);
char		**ft_split_charset(char *str, char *charset);
void		ft_print_list(t_list *list);
int			ft_is_nbr(char *str);
long long	ft_long_atoi(const char *str);
int			get_next_line(int fd, char **line);
void		ft_lstadd_front(t_list **alst, t_list *new);
size_t		ft_strlen(char const *str);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strdup(const char *src);
char		*ft_strncat(char *dest, const char *src, size_t n);
char		*ft_strncpy(char *dest, const char *src, size_t n);
void		*ft_memset(void *s, char c, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(char const *s1, char const *s2, unsigned int n);
int			ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isspace(const char str);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, void const *src, size_t n);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memmove(void *dest, void const *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(void const *s1, void const *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strnstr(char const *str, char const *to_find, size_t len);
size_t		ft_strlcat(char *dest, char *src, size_t size);
void		ft_memdel(void **ap);
void		*ft_memalloc(size_t size);
void		ft_putchar(int c);
void		ft_putstr(char const *str);
void		ft_putnbr(int nb);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strnew(size_t size);
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl(char const *s);
char		*ft_itoa(int n);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlcpy(char *dest, char const *src, size_t size);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstadd_back(t_list **alst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
void		ft_del_list(void *grid);

#endif
