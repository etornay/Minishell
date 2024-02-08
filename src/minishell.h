/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:34:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/08 13:00:54 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
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
	char	*act_dir;
	char	**lex;
	char	*tmp;
	char	*cd_error;
	int		i;
	int		c;
	int		j;
	int		double_flag;
	int		simple_flag;
	t_env	*l_env;
	t_env	*aux;
	t_env	*first;
}	t_paco;

int		get_path(t_paco *p, char **env);
void	lst_addenv_back(t_env **lst, t_env *new, char **tmp);
void	init_env(t_paco *p, char **env, int i);
void	exec_pwd(t_paco *p);
void	flag_echo(char **s, int flag, t_paco *p);
void	exec_env(t_paco *p);
int		prompt(t_paco *p);
void	ft_paco_sanz(void);
void	ft_paco_sanz2(void);
char	**split_line(char *s, char limit, t_paco *p);
int		input(char *input, t_paco *p, char **env);
void	init_struct(t_paco *p);
int		ft_exp_cmp(const char *s1, const char *s2);
void	set_env_index(t_paco *p);
int		ft_env_size(t_env *lst);
void	exec_export(t_paco *p);
void	exec_unset(t_paco *p, char *name);
void	free_mini_split(char **s, int j);
void	get_cd_path(t_paco *p, char *s);
void	change_oldpwd(t_paco *p);
void	change_oldpwd2(t_paco *p, char *dir);
void	exec_cd(t_paco *p, char **s);
void	change_pwd(t_paco *p);
void	change_cd(t_paco *p, int option);
void	restart_index(t_paco *p);
void	lstadd_oldpwd(t_paco *p);
void	gen_oldpwd(t_paco *p);
int	check_oldpwd(t_paco *p);

#endif