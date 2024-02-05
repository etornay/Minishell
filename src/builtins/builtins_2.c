/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:33:49 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/05 12:02:25 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_paco *p, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p->lex[i] != NULL)
		i++;
	while (p->lex[i][j] != '\0')
	{
		
	}
	if (flag == 1)
		printf("\n");
}
