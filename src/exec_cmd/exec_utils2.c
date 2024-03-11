/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:07:02 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/11 19:51:10 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	final_exit(t_paco *p, t_parser *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->full_cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("exit\nPACOSHELL: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (i >= 2)
	{
		while (node->full_cmd[1][j] != '\0')
		{
			if (ft_isdigit(node->full_cmd[1][j]) == 0)
			{
				printf("PACOSHELL: exit: %s: numeric argument required\n",
					node->full_cmd[1]);
				break ;
			}
			j++;
		}
	}
	free_path(p);
	exit(g_status);
}
