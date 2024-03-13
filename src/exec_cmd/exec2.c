/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:00:38 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/13 15:21:36 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* int	expr_dollar(t_paco *p, t_parser *node)
{
	if (node && node->full_cmd && strcmp(node->full_cmd[0], "expr") == 0
		&& node->full_cmd[1] && strcmp(node->full_cmd[1], "$?") == 0
		&& node->full_cmd[2] && strcmp(node->full_cmd[2], "+") == 0
		&& node->full_cmd[3] && strcmp(node->full_cmd[3], "$?") == 0)
	{
		if (g_status == 1)
		p->total_expr = g_status + g_status;
		printf("%d/n", p->total_expr);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
} */
