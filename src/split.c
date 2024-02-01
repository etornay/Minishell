/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:15:18 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/01 19:25:32 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	word_len2(char *s, char d, t_paco *p)
{
	p->c = p->i;
	if (s[p->i] == '\"' || s[p->i] == '\'')
		p->i++;
	while (s[p->i] != '\0')
	{
		while (((s[p->i] != '\"' && p->double_flag) || s[p->i] != d) && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == d)
			break ;
	}
} */

static int	word_len(char *s, char d, t_paco *p)
{
	while (s[p->i] != '\0')
	{
		while (s[p->i] == d && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == '\"' && p->simple_flag == 0)
		{
			p->double_flag = !p->double_flag;
		}
		if (s[p->i] == '\'' && p->double_flag == 0)
		{
			p->simple_flag = !p->simple_flag;
		}
		p->c = p->i;
		if (s[p->i] == '\"' || s[p->i] == '\'')
			p->i++;
		while (s[p->i] != '\"' && p->double_flag)
			p->i++;
		if (s[p->i] == '\"')
			p->double_flag = !p->double_flag;
		while (s[p->i] != d && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == d || s[p->i] == '\0')
			break ;
	}
	return (p->i - p->c);
}

static char	**split_loop(char *s, char limit, char **str, t_paco *p)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	p->c = 0;
	while (s[i] != '\0')
	{
		while (s[i] == limit && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		len = word_len(s, limit, p);
		str[j] = malloc((len + 1) * sizeof(char *));
		if (!str[j])
		{
			free_mini_split(str, j);
			return (NULL);
		}
		ft_strlcpy(str[j], s + p->c, len + 1);
		i += len;
		j++;
	}
	return (str[j] = NULL, str);
}

static int	count_words(char *s, char d, t_paco *p)
{
	while (s[p->i] != '\0')
	{
		while (s[p->i] == d && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == '\"' || s[p->i] == '\'')
		{
			if (s[p->i] == '\"')
			{
				p->i++;
				while (s[p->i] != '\0' && (s[p->i] != '\"' || s[p->i + 1] != d))
					p->i++;
			}
			else if (s[p->i] == '\'')
			{
				p->i++;
				while (s[p->i] != '\0' && (s[p->i] != '\'' || s[p->i + 1] != d))
					p->i++;
			}
		}
		if (s[p->i] != '\0')
			p->c++;
		while (s[p->i] != d && s[p->i] != '\0')
			p->i++;
	}
	return (p->i = 0, p->c);
}

char	**split_line(char *s, char limit, t_paco *p)
{
	char	**str;

	if (!s)
		return (NULL);
	str = malloc((count_words(s, limit, p) + 1) * sizeof(char **));
	if (!str)
		return (NULL);
	str = split_loop(s, limit, str, p);
	if (!str)
	{
		free_mini_split(str, count_words(s, limit, p));
		return (NULL);
	}
	return (str);
}
