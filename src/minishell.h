/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:34:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:57 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# define RED_T "\x1b[1;31m"
# define YELLOW_T "\x1b[1;33m"
# define PURPLE_T "\033[35m"
# define RESET_COLOR "\x1b[0m"

typedef struct s_paco
{
	char	*shell;
	char	*line;
}	t_paco;

#endif