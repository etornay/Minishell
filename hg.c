/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:58:12 by etornay-          #+#    #+#             */
/*   Updated: 2024/01/31 18:33:39 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

echo "hello  there" how you "you"doing?

static void	word_len2(char *s, char d, t_paco *p)
{
	p->c = p->i;
	if (s[p->c] == '\"')
	{
		p->c++;
		while (s[p->c] != '\0' && (s[p->c] != '\"' || s[p->c + 1] != d))
			p->c++;
	}
	else if (s[p->c] == '\'')
	{
		p->c++;
		while (s[p->c] != '\0' && (s[p->c] != '\'' || s[p->c + 1] != d))
			p->c++;
	}
}

static int	word_len(char *s, char d, t_paco *p)
{
	p->c = 0;
	p->i = 0;
	while (s[p->i] != '\0')
	{
		while (s[p->i] == d && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == '\"' || s[p->i] == '\'')
		{
			word_len2(s, d, p);
		}
 		while (s[p->i] != d && s[p->i] != '\0')
			p->i++;
	}
	return (p->i - p->c);
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
				while (s[p->i] != '\0' && s[p->i] != '\'')
					p->i++;
			}
		}
		if (s[p->i] != '\0')
			p->c++;
		while (s[p->i] != d && s[p->i] != '\0')
			p->i++;
	}
	return (p->c);
}

#include <stdio.h>
int	main(void)
{
	printf("%d",count_words("echo \"hello  there\" how are 'you 'doing? $USER |wc -l >>out", ' '));
	return (0);
}
