/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:19:40 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/05 15:46:41 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_errors6(t_paco *p, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1] == NULL)
	{
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1] == NULL)
	{
		printf("PACOSHELL: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	token_errors5(t_paco *p, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2] == NULL)
	{
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '<')
	{
		printf("PACOSHELL: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2] == NULL)
	{
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors6(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
