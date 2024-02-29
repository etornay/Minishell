/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:25:07 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/29 17:30:05 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_errors4(t_paco *p, int *i)
{
	else if (p->lex2[*i + 1][0] == '<')
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	token_errors3(t_paco *p, int *i)
{
	else if (p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] == '>')
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] == '<')
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2][0] == '<')
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '>')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors4(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	token_errors2(t_paco *p, int *i)
{
	else if (p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] == '>'
		&& p->lex2[*i + 3][0] == '<')
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2][0] == '<'
		&& p->lex2[*i + 3][0] == '>')
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] == '<'
		&& p->lex2[*i + 3][0] == '>')
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors3(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	token_errors(t_paco *p, int *i)
{
	if (p->lex2[*i + 1] == NULL)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2][0] == '<'
		&& p->lex2[*i + 3][0] == '<' && p->lex2[*i + 4][0] == '>')
	{
		printf("bash: syntax error near unexpected token `<>'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] == '>'
		&& p->lex2[*i + 3][0] == '<' && p->lex2[*i + 4][0] == '>')
	{
		printf("bash: syntax error near unexpected token `<>'\n");
		return (EXIT_FAILURE);
	}
	if (token_errors2(p, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
