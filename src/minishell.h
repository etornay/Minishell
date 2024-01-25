/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:34:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/01/25 09:41:37 by ncruz-ga         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*content;
	int				index;
	struct s_env	*next_env;
}	t_env;

typedef struct s_paco
{
	char	*shell;
	char	*line;
	char	**path;
	t_env	*l_env;
	t_env	*aux;
}	t_paco;

int	get_path(t_paco *p, char **env);

#endif