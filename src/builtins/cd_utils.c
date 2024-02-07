/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:50:53 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/07 13:27:41 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_path(t_paco *p, char *s)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
		{
			
		}
			
	}
}
