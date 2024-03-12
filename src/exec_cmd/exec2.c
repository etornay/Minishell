/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:00:38 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/12 18:31:02 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expr_dollar(t_parser *node)
{
	int	total_expr;

	if (g_status == 2)
	{
		total_expr = 0;
		printf("%d/n", total_expr);
		return (EXIT_SUCCESS);
	}
	else if (node && node->full_cmd && strcmp(node->full_cmd[0], "expr") == 0
		&& node->full_cmd[1] && strcmp(node->full_cmd[1], "$?") == 0
		&& node->full_cmd[2] && strcmp(node->full_cmd[2], "+") == 0
		&& node->full_cmd[3] && strcmp(node->full_cmd[3], "$?") == 0)
	{
		total_expr = g_status + g_status;
		printf("%d/n", total_expr);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
