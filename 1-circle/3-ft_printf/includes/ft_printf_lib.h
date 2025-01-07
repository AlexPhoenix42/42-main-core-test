/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:40:31 by codespace         #+#    #+#             */
/*   Updated: 2024/12/27 14:00:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_PRINTF_LIB_H
#define	FT_PRINTF_LIB_H

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
// #include <stdio.h>

typedef struct t_printf_form
{
	size_t	i;
	char	*is_found;
	char	flags[6];
	char	form;
	char	*widthc;
	char	*precisionc;
	char	hex_ox[3];
	char	boolen;
	size_t	width;
	size_t	precision;
}	t_printf_form;

int		ft_printf(const char *str0, ...);

int		ft_printf_logic(char *str, va_list args);
// void	init_printf_form(t_printf_form *form_found, char *is_found);
// void	get_form(char *str, char *flags, char *forms,
// 			t_printf_form *form_found);
// void	get_form_logic(char *str, char *flags, char *forms,
// 			t_printf_form *form_found);
// void	check_form_logic(size_t i, char *str, char *flags,
// 			t_printf_form *form_found);

size_t	char_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str);
size_t	str_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str);
char	*ft_print_char(char *str, char **ptr, size_t *len_r, ssize_t n);
char	*ft_print_char0(char *str, char **ptr, size_t *len_r, ssize_t n);

int		process_arg(va_list args, char **str,
			t_printf_form *form_found, size_t *len_r);

size_t	ptr_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str);
size_t	hex_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str);
size_t	uint_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str);
size_t	int_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str);

size_t	hex_printf_prefix_cnd(t_printf_form *form_found, size_t hex_len,
			char *flags, unsigned int ux);
size_t	hex_printf_logic_cnd(t_printf_form *form_found, size_t hex_len,
			char *flags, unsigned int ux);
size_t	int_printf_logic_prefix0_cnd(t_printf_form *form_found, size_t int_len,
			char *flags, int x);

#endif
