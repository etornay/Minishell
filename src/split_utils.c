/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:20:20 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/02 11:57:58 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	word_len2(char *s, char d, t_paco *p)
{
	p->c = p->i;
	if (s[p->i] == '\"' || s[p->i] == '\'')
		p->i++;
	while (s[p->i] != '\0')
	{
		while (((s[p->i] != '\"' && p->double_flag) || s[p->i] != d) && s[p->i] != '\0')
			p->i++;
		if (s[p->i] == d)
			break ;
	}
} */