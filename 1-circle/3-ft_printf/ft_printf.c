/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:06:10 by codespace         #+#    #+#             */
/*   Updated: 2024/12/15 07:23:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include "./includes/ft_printf_lib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <stdint.h>

// https://manp.gs/mac/3/printf
// https://manp.gs/mac/3/stdarg

// My ft_printf() just broke the system.
// I dont know how is it bypassing the system's
// security out of bounds check!!!!
// My ft_printf() can read beyond the allowed memory!!!!

// cc -g -O0 -Wall -Wextra -Werror 13.c
// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out

//static size_t	ft_printnstr(const char *str, va_arg(args, void*), size_t n);

int	ft_printf(const char *str0, ...);

/*
	These functions return the number of characters printed (not including
	the trailing `\0' used to end output to strings) or a negative value if
	an output error occurs, except for snprintf() and vsnprintf(), which
	return the number of characters that would have been printed if the n
	were unlimited (again, not including the final `\0').
*/
int	ft_printf(const char *str0, ...)
{
	size_t	len_r;
	va_list	args;
	char	*str;

	str = malloc(ft_strlen(str0) * sizeof(char));
	if (!str)
		return (-1);
	ft_memcpy(str, str0, ft_strlen(str0) + 1);
	va_start(args, str0);
	len_r = ft_printf_logic(str, args);
	free(str);
	return ((int) len_r);
}
