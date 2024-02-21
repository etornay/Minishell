/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:09:40 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/19 16:41:58 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lex2(t_paco *p)
{
	int	i;

	i = 0;
	if (p->lex2 != NULL)
	{
		while (p->lex2[i])
		{
			free(p->lex2[i]);
			p->lex2[i++] = NULL;
		}
		free(p->lex2);
		p->lex2 = NULL;
	}
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free (tmp);
}

void	free_cd_error(t_paco *p)
{
	free(p->tmp);
	free(p->cd_error);
}
