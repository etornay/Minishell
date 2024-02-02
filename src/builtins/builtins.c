/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:51:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/02 12:01:49 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_paco *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
}

void	exec_echo(char **s, int size)
{
	int	i;

	i = 0;
	while (s[size][i])
	{
		
	}
}

void	echo(char **s, int flag)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i > 1)
	{
		if (ft_strncmp (s[2], "-n\0", 3) == EXIT_FAILURE)
		{
			flag = 1;
			i = 3;
		}
		else
			i = 2;
		while (s[i] != NULL)
		{
			exec_echo(s, i);
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
}
