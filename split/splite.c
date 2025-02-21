/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alephoen <alephoen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:09:03 by alephoen          #+#    #+#             */
/*   Updated: 2025/02/21 22:00:58 by alephoen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc -g -fsanitize=address,undefined -Werror -Wextra -Wall *.c

// #include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char *str, char *charset);
char	**init_check(char *str, char *charset,
			size_t *ss_len, char **strptr);
char	*findstr(char **strptr, char *charset, size_t *ss_len);
char	*ft_strndup(char *src, size_t size);
char	*ft_strnstr(char *str, char *to_find, size_t size, size_t *setlen);

// ss_len[0] = size;
// ss_len[1] = setlen;
// ss_len[2] = i;
// *strptr[0] = *strptr0;
// *strptr[1] = *strptr
char	**ft_split(char *str, char *charset)
{
	size_t	ss_len[3];
	char	*strptr[2];
	char	**strs;

	ss_len[2] = 2;
	ss_len[0] = 0;
	if (!str || !(*str) || !charset || !(*charset))
		return (init_check(str, charset, ss_len, strptr));
	init_check(str, charset, ss_len, strptr);
	strptr[0] = strptr[1];
	while (strptr[1] && strptr[1][0] && ++ss_len[0])
	{
		strptr[1] = ft_strnstr(strptr[1], charset, 0, NULL);
		if (strptr[1] && strptr[1][0] != '\0')
			strptr[1] += ss_len[1];
	}
	strs = (char **) malloc(sizeof(char *) * (ss_len[0] + 1));
	if (!strs)
		return (strs);
	strs[ss_len[0]] = 0;
	strptr[1] = strptr[0];
	ss_len[2] = -1;
	while (++(ss_len[2]) < ss_len[0])
		strs[ss_len[2]] = findstr(&strptr[1], charset, ss_len);
	return (strs);
}

// ss_len[0] = size;
// ss_len[1] = setlen;
// ss_len[2] = i;
// *strptr[0] = *strptr0;
// *strptr[1] = *strptr
char	**init_check(char *str, char *charset,
			size_t *ss_len, char **strptr)
{
	char	**strs;

	if (!str)
		ss_len[2] = 1;
	if (!str || !(*str) || !charset || !(*charset))
		strs = (char **) malloc(sizeof(char *) * ss_len[2]);
	if (!str)
		*strs = 0;
	else if (str && (!(*str) || !charset || !(*charset)))
		strs[1] = 0;
	if (str && !(*str))
		strs[0] = ft_strndup("\0", 1);
	else if (!charset || !(*charset))
		strs[0] = ft_strndup(str, 0);
	if (!str || !(*str) || !charset || !(*charset))
		return (strs);
	ss_len[0] = 0;
	ss_len[1] = 0;
	ss_len[2] = 0;
	strptr[1] = str;
	if (ft_strnstr(strptr[1], charset, ss_len[1], &ss_len[1]) == str)
		while (strptr[1] != 0 && ++(ss_len[2]) < ss_len[1] + 1)
			++(strptr[1]);
	return (strs);
}

char	*ft_strndup(char *src, size_t size)
{
	size_t	i;
	char	*str;

	if (!src)
		return (NULL);
	i = -1;
	while ((src[++i] != '\0' && i < size) || (src[i] != '\0' && size == 0)) 
		;
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while ((src[++i] != '\0' && i < size) || (src[i] != '\0' && size == 0))
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}

// ss_len[0] = strlen;
// ss_len[1] = setlen;
char	*findstr(char **strptr, char *charset, size_t *ss_len)
{
	char	*str;
	char	*beg;
	char	*end;

	beg = *strptr;
	end = ft_strnstr(*strptr, charset, 0, NULL);
	if (end)
	{
		if (**strptr != '\0')
		{
			str = ft_strndup(*strptr, (end - beg));
			(*strptr) += (end - beg) + ss_len[1];
			return (str);
		}
	}
	else if (**strptr != '\0')
	{
		str = ft_strndup(*strptr, (end - beg));
		*strptr += ss_len[1];
		return (str);
	}
	return (NULL);
}

char	*ft_strnstr(char *str, char *to_find, size_t size, size_t *setlen)
{
	size_t	i;
	size_t	j;

	if (setlen)
		setlen[1] = 0;
	while (setlen != NULL && *to_find && to_find[*setlen])
		++(*setlen);
	if (!to_find || !(*to_find))
		return (str);
	i = -1;
	while ((str[++i] != '\0' && i < size)
		|| (size == 0 && str[i] != '\0'))
	{
		j = 0;
		while (to_find[j] != '\0' && to_find[j] == str[i + j])
			++j;
		if (to_find[j] == '\0')
			return (&(str[i]));
	}
	return (NULL);
}

/*
// "                 ",
// "00000000000000000" 
// "00000"     "     "
int	main(void)
{
	size_t	i;
	size_t	size;
	char	**strs;

	strs = NULL;

	// ^&*Hello, My ^&*fiend^&*Yes^&*		^&*

	size = 4;
	// strs = ft_split("                 ", "     ");
	// strs = ft_split("00000000000000000", "00000");
	// strs = ft_split("^&*Hello, My ^&*fiend^&*Yes^&*", "^&*");
	// strs = ft_split("^&*Hello, My ^&*fiend^&*Yes", "^&*");
	// strs = ft_split("Hello, My ^&*fiend^&*Yes^&*", "^&*");
	// strs = ft_split("Hello, My ^&*fiend^&*Yes", "^&*");

	// size = 0;
	// strs = ft_split(NULL, NULL);	// change size to 0;
	// strs = ft_split(NULL, "");
	// strs = ft_split(NULL, "^&*");

	// size = 1;
	// strs = ft_split("", "");
	// strs = ft_split("", NULL);

	// size = 2;
	// strs = ft_split("^&*Hello, My ^&*fiend^&*Yes^&*", NULL);

	i = -1;
	while (strs && ++i < size)
		printf("|%s|\n", strs[i]);
	if (strs)
	{
		i = -1;
		while (++i < size)
			if (strs[i])
				free(strs[i]);
		free(strs);
	}
	return (0);
}
*/


/*
Trace:

> cc -Wextra -Wall -Werror main.c ft_split.c -o user_exe
= Test 1 ===================================================
$> ./ehjtpyd829plzvuqf5oyufae "                 " "     "
$> diff -U 3 user_output_test1 test1.output | cat -e
--- user_output_test1    2025-02-21 19:26:10.555427539 +0000$
+++ test1.output    2025-02-21 19:26:10.527427645 +0000$
@@ -1,5 +1,3 @@$
                        $
tab start$
-tab[0]:              $
-tab[1]:         $
tab end$
Diff KO :(
Grade: 0
= Final grade: 80 ==============================================================
*/
