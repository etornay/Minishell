/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   COSAS.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:58:12 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/01 18:09:54 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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