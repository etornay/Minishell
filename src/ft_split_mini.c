/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:09:34 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/15 14:25:29 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		fq_simple;
	int		fq_double;

	count = 0;
	fq_simple = 0;
	fq_double = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
			count++;
		while ((*s != c || (*s == c && (fq_double || fq_simple))) && *s != '\0')
		{
			if (*s == '\'' && !fq_double)
				fq_simple = !fq_simple;
			else if (*s == '\"' && !fq_simple)
				fq_double = !fq_double;
			s++;
		}
	}
	return (count);
}

static void	ft_free_split(char **arr, size_t index)
{
	size_t	i;

	if (arr != NULL)
	{
		i = 0;
		while (i < index)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static size_t	word_length(const char *s, char delimiter)
{
	size_t	len;
	int		fq_simple;
	int		fq_double;

	len = 0;
	fq_simple = 0;
	fq_double = 0;
	while ((s[len] != delimiter || (fq_double || fq_simple)) && s[len] != '\0')
	{
		if (s[len] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[len] == '\"' && !fq_simple)
			fq_double = !fq_double;
		len++;
	}
	return (len);
}

static char	**split_loop(const char *s, char delimiter, char **new_str)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s != '\0')
	{
		while (*s == delimiter && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		word_len = word_length(s, delimiter);
		new_str[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!new_str[i])
		{
			ft_free_split(new_str, i);
			return (NULL);
		}
		ft_strlcpy(new_str[i], (char *)s, word_len + 1);
		s += word_len;
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

char	**ft_split_mini(const char *s, char delimiter)
{
	char	**new_str;

	new_str = (char **)malloc((count_words(s, delimiter) + 1) * sizeof(char *));
	if (!new_str || !s)
		return (NULL);
	new_str = split_loop(s, delimiter, new_str);
	if (!new_str)
		return (ft_free_split(new_str, count_words(s, delimiter)), NULL);
	return (new_str);
}
