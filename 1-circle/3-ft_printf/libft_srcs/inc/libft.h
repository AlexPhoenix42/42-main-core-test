/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:55:37 by codespace         #+#    #+#             */
/*   Updated: 2024/12/27 14:00:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBFT_H
#define	LIBFT_H

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

// standard_libft_1:
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_memchr(char *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isdigit_pls(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

// standard_libft_2:
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);

// standard_libft_3:
int		string2int(char *str, int sign);
size_t	wint2base(int nbr, char *base, unsigned int baselen);
size_t	wint2base_minus(int nbr, char *base, unsigned int baselen);
size_t	wuint2base(unsigned int nbr, char *base, unsigned int baselen);
void	wint2hex(int nbr, char upper, size_t position);

size_t	getintlen(signed long long int x);
size_t	hex_len_pointer(void *ptr);
size_t	hex_len_uint(unsigned int ux);

void	getptradrs2hex(uintptr_t nbr, size_t position);

// _bonus:
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

#endif
