/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:25:07 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/05 15:46:06 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_errors4(t_paco *p, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '<'
		&& p->lex2[*i + 1] && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2] && p->lex2[*i + 2][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `>'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2]
		&& p->lex2[*i + 2][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `>'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2]
		&& p->lex2[*i + 2][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `<>'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors5(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	token_errors3(t_paco *p, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2] && p->lex2[*i + 2][0] == '<')
	{
		printf("PACOSHELL: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '>'
		&& p->lex2[*i + 1] && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2] && p->lex2[*i + 2][0] == '<')
	{
		printf("PACOSHELL: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '>'
		&& p->lex2[*i + 1] && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2] && p->lex2[*i + 2][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `>'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors4(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	token_errors2(t_paco *p, int *i)
{
	if ((p->lex2[*i] && (p->lex2[*i][0] == '<' || p->lex2[*i][0] == '>'))
		&& ((p->lex2[*i + 1] && (p->lex2[*i + 1][0] == '<'
		|| p->lex2[*i + 1][0] == '>' || p->lex2[*i + 1][0] == '|'))
		|| (p->lex2[*i + 2] && p->lex2[*i + 2][0] == '|')
		|| (p->lex2[*i + 3] && p->lex2[*i + 3][0] == '|')))
	{
		printf("PACOSHELL: syntax error near unexpected token `|'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors3(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	token_errors(t_paco *p, int *i)
{
	if (p->lex2[*i] && p->lex2[*i] == NULL)
	{
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2]
		&& p->lex2[*i + 2][0] == '<' && p->lex2[*i + 3]
		&& p->lex2[*i + 3][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `<>'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1]
		&& p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2]
		&& p->lex2[*i + 2][0] == '<' && p->lex2[*i + 3]
		&& p->lex2[*i + 3][0] == '>')
	{
		printf("PACOSHELL: syntax error near unexpected token `<>'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors2(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
