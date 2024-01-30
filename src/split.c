/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:15:18 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/01/30 13:34:15 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **s, int j)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (i < j)
		{
			if (s[i])
				free(s[i]);
			i++;
		}
		free(s);
	}
}

static int	word_len(char *s, char limit)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != limit)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"' && s[i] != '\'')
				i++;
		}
		else
			i++;
	}
	return (i);
}

static char	**split_loop(char *s, char limit, char **str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == limit && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		len = word_len(s, limit);
		str[j] = malloc((len + 1) * sizeof(char *));
		if (!str[j])
		{
			free_split(str, j);
			return (NULL);
		}
		ft_strlcpy(str[j], s, len + 1);
		i += len;
		j++;
	}
	str[j] = NULL;
	return (str);
}

static int	count_words(char *s, char limit)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"' && s[i] != '\'')
				i++;
			c++;
		}
		else
		{
			while (s[i] == limit && s[i] != '\0')
				i++;
			if (s[i] != '\0')
				c++;
		}
	}
	return (c);
}

char	**split_line(char *s, char limit)
{
	char	**str;

	if (!s)
		return (NULL);
	str = malloc((count_words(s, limit) + 1) * sizeof(char **));
	if (!str)
		return (NULL);
	str = split_loop(s, limit, str);
	if (!str)
	{
		free_split(str, count_words(s, limit));
		return (NULL);
	}
	return (str);
}
