/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:51:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/01/30 13:30:02 by ncruz-ga         ###   ########.fr       */
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

/* void	echo(t_paco *p, int flag)
{
	
} */
