/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:51:00 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/01 16:04:48 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
//# include <stdio.h>
//# include <string.h>

typedef struct s_input
{
	char			**cmd;
	char			**red;
	int				*type;
	int				*is_qouts;
	int				len;
	struct s_input	*next;
}	t_input;
/*

*/
// parte 1

void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *s, int c);
void				*ft_memset(void *ptr, int c, size_t len);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
void				ft_bzero(void *s, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_atoi(const char *str);
char				*ft_strnstr(const char *h, const char *n, size_t len);
char				*ft_strdup(const char *s1);
void				*ft_calloc(size_t count, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
// part 2
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// bonus :)

t_input				*ft_lstnew(void);
t_input				*ft_lstlast(t_input *lst);
void				ft_lstadd_back(t_input **lst, t_input *new);

#endif