/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:27:59 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/14 15:01:59 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_content(t_paco *p, char *s)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
			return (ft_strdup(p->aux->content));
		p->aux = p->aux->next_env;
	}
	return (ft_strdup(""));
}

static void	expand_1(t_paco *p, int	*i, int *flag, char **expand)
{
	char	*tmp;

	if (p->lex[p->i][p->j] == '$' && !*flag)
	{
		if (p->lex[p->i][p->j + 1] == '\0' || p->lex[p->i][p->j + 1] == ' ')
		{
			*expand = ft_strjoin_gnl2(*expand, ft_strdup("$"));
			p->j++;
		}
		else
		{
			p->j++;
			*i = p->j;
			while ((p->lex[p->i][p->j] != ' ' && p->lex[p->i][p->j] != '$'
				&& p->lex[p->i][p->j] != '\0') && p->lex[p->i][p->j] != '\''
				&& p->lex[p->i][p->j] != '\"')
				p->j++;
			tmp = ft_substr(p->lex[p->i], *i, p->j - *i);
			*expand = ft_strjoin_gnl2(*expand, get_env_content(p, tmp));
			free(tmp);
			tmp = NULL;
		}
	}
}

static void	expand_2(t_paco *p, int *i, int *flag, char **exp)
{
	if ((!*flag && p->lex[p->i][p->j] == '~')
		&& ((p->lex[p->i][p->j - 1] == ' ' && p->lex[p->i][p->j + 1] == ' ')
		|| (p->lex[p->i][p->j + 1] == '\0') || (p->lex[p->i][p->j + 1] == '/')))
	{
		if (p->lex[p->i][p->j] == '\'')
			*flag = !*flag;
		*exp = ft_strjoin_gnl2(*exp, get_env_content(p, "HOME"));
		p->j++;
	}
	else
	{
		*i = p->j;
		while ((p->lex[p->i][p->j] != '$' || *flag)
			&& p->lex[p->i][p->j] != '\0')
		{
			if (p->lex[p->i][p->j] == '\'')
				*flag = !*flag;
			p->j++;
		}
		*exp = ft_strjoin_gnl2(*exp, ft_substr(p->lex[p->i], *i, p->j - *i));
	}
}

void	expand(t_paco *p)
{
	int		i;
	int		flag;
	char	*expand;

	expand = NULL;
	flag = 0;
	p->i = -1;
	while (p->lex[++p->i])
	{
		p->j = 0;
		i = 0;
		while (p->lex[p->i][p->j])
		{
			expand_1(p, &i, &flag, &expand);
			expand_2(p, &i, &flag, &expand);
		}
		free(p->lex[p->i]);
		p->lex[p->i] = NULL;
		p->lex[p->i] = ft_strdup(expand);
		free(expand);
		expand = NULL;
	}
	p->i = 0;
	p->j = 0;
}
