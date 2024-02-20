/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   COSAS.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:58:12 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/20 15:54:33 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

- ARREGLAR COMANDOS AL ESCRIBIR DE MAS

echo "hello  there" how you "you"doing?
echo "hello  there" how you "you"doing?

static void	word_len2(char *s, char d, t_paco *p)
{
	p->c = p->i;
	if (s[p->i] == '\"')
	{
		p->i++;
		while (s[p->i] != '\0')
		{
			if (s[p->i] == '\"' && (s[p->i + 1] == d || s[p->i + 1] == '\0'))
				break ;
			else if (s[p->i] == d && s[p->i + 1] == '\"' && s[p->i + 2] == d)
				break ;
			else if (s[p->i] == d && s[p->i + 1] == '\"' && s[p->i + 2] != d)
				p->i++;
			else if ((s[p->i] == '\"' || s[p->i] != '\"') && (s[p->i + 1] != d || s[p->i + 1] != '\0'))
				p->i++;
			else if (s[p->i] != '\"' && s[p->i + 1] == d)
				p->i++;
			else
				p->i++;
		}
		if (s[p->i] != '\0')
			p->i++;
	}
	else if (s[p->i] == '\'')
	{
		p->i++;
		while (s[p->i] != '\0')
		{
			if (s[p->i] == '\'' && (s[p->i + 1] == d || s[p->i + 1] == '\0'))
				break ;
			else if ((s[p->i] == '\'' || s[p->i] != '\"') && (s[p->i + 1] != d || s[p->i + 1] != '\0'))
				p->i++;
			else if (s[p->i] != '\'' && s[p->i + 1] == d)
				p->i++;
			else
				p->i++;
		}
		if (s[p->i] != '\0')
			p->i++;
	}
}

static int	word_len(char *s, char d, t_paco *p)
{
	while (s[p->i] != '\0')
	{
		while (s[p->i] == d && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == '\"' || s[p->i] == '\'')
			word_len2(s, d, p);
		if (s[p->i] != '\0' && s[p->i] != d)
		{
			p->c = p->i;
			while (s[p->i] != d && s[p->i] != '\0')
				p->i++;
		}
		if (s[p->i] == d)
		{
			s += p->i;
			break ;
		}
	}
	return (p->i - p->c);
}

void	pecho(char **s, int flag, t_paco *p)
{
	while (s[p->j])
		p->j++;
	if (p->j > 1)
	{
		if (ft_strncmp (s[1], "-n\0", 3) == EXIT_SUCCESS)
		{
			flag = 1;
			p->j = 2;
		}
		else
			p->j = 1;
		while (s[p->j] != NULL)
		{
			exec_echo(s, p->j, p);
			if (s[p->j + 1])
				ft_printf(" ");
			p->j++;
			if (p->double_flag == 1)
				p->double_flag = 0;
			if (p->simple_flag == 1)
				p->simple_flag = 0;
		}
	}
	if (flag == 0)
		ft_printf("\n");
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


/* ((s[p->l] != '|' && s[p->l] != '>' && s[p->l] != '<')
				&& (!fq_double || !fq_simple)) || ((fq_double || fq_simple)
				&& (s[p->l] != '|' && s[p->l] != '>' && s[p->l] != '<')) */

/* if ((s[p->l + 1] == '|' || s[p->l + 1] == '>' || s[p->l + 1] == '<')
	&& (!fq_double && !fq_simple))
	return (len); */