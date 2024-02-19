/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:01:04 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/19 11:20:08 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	word_len(char *s, char d)
{
	size_t	len;
	int		fq_simple;
	int		fq_double;

	len = 0;
	fq_simple = 0;
	fq_double = 0;
	while ((s[len] != d || (fq_double || fq_simple)) && s[len] != '\0')
	{
		if (s[len] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[len] == '\"' && !fq_simple)
			fq_double = !fq_double;
		len++;
	}
	return (len);
}

static char	**split_loop(char *s, char limit, char **str)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s != '\0')
	{
		while (*s == limit && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		len = word_len(s, limit);
		str[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!str[i])
		{
			free_mini_split(str, i);
			return (NULL);
		}
		ft_strlcpy(str[i], s, len + 1);
		s += len;
		i++;
	}
	str[i] = NULL;
	return (str);
}

static int	count_words2(char **s, int *fq_simple, int *fq_double, t_paco *p)
{
	
}

static int	count_words(char **s, char d, t_paco *p)
{
	size_t	count;
	int		fq_simple;
	int		fq_double;

	count = 0;
	fq_simple = 0;
	fq_double = 0;
	p->i = 0;
	while (s[p->i] != NULL)
	{
		p->j = 0;
		while (s[p->i][p->j])
		{
			count_words2(s, &fq_simple, &fq_double, p);
			if ((s[p->i][p->j] == '<' || s[p->i][p->j] == '|'
				|| s[p->i][p->j] == '>') && !fq_simple && !fq_double)
			{
				count++;
			}
			p->j++;
		}
		p->i++;
	}
	return (count);
}

char	**split_pipe(char **s, char limit, t_paco *p)
{
	char	**str;

	if (!s)
		return (NULL);
	p->i = 0;
	str = malloc((count_words(s, limit, p) + 1) * sizeof(char **));
	if (!str)
		return (NULL);
	str = split_loop(s, limit, str);
	if (!str)
	{
		free_mini_split(str, count_words(s, limit, p));
		return (NULL);
	}
	return (str);
}
