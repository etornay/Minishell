/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:34:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/11 19:17:21 by etornay-         ###   ########.fr       */
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

int	g_status;

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
	char	**lex2;
	char	*tmp;
	char	*tmp_cmd;
	char	*tmp_path;
	char	*cd_error;
	char	*eof;
	char	*heredoc_line;
	int		dup_stdin;
	int		dup_stdout;
	int		i;
	int		c;
	int		j;
	int		k;
	int		l;
	int		n_split;
	int		double_flag;
	int		simple_flag;
	int		count;
	int		wc;
	int		heredoc_tmp;
	int		heredoc_flag;
	int		pipe_flag;
	int		wait;
	int		fd[2];
	pid_t	pid;
	size_t	wordle;
	t_env	*l_env;
	t_env	*aux;
	t_env	*first;
	t_list	*clean;
	t_list	*lst_cmd;
}	t_paco;

typedef struct s_parser
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}	t_parser;

/*--- <MINISHELL> ---*/
int		input(char *input, t_paco *p, char **env);
int		get_path(t_paco *p, char **env);
char	**split_line(char *s, char limit, t_paco *p);
void	expand(t_paco *p);
char	**split_pipe(char **s, t_paco *p, int i, int j);

/*--- <MINISHELL DESIGN> ---*/
int		prompt(t_paco *p);
void	ft_paco_sanz(void);
void	ft_paco_sanz2(void);

/*--- <INIT MINISHELL> ---*/
void	init_struct(t_paco *p);

/*--- <BUILTINS> ---*/
void	exec_pwd(t_paco *p);
void	exec_env(t_paco *p);
void	exec_export(t_paco *p, char **s, int index);
void	exec_unset(t_paco *p, char *name);
void	exec_cd(t_paco *p, char **s, int flag);
void	flag_echo(char **s, int flag, t_paco *p);
int		final_exit(t_paco *p, t_parser *node);

/*--- <BUILTINS UTILS> ---*/
void	lst_addenv_back(t_env **lst, t_env *new, char **tmp);
void	init_env(t_paco *p, char **env, int i);
void	get_cd_path(t_paco *p, char *s);
void	change_pwd(t_paco *p);
void	change_cd(t_paco *p);
void	change_oldpwd(t_paco *p);
void	change_oldpwd2(t_paco *p, char *dir);
int		ft_exp_cmp(const char *s1, const char *s2);
void	set_env_index(t_paco *p);
int		ft_env_size(t_env *lst);
int		check_node(t_paco *p, char **s);
void	ft_env_clear(t_env **lst);
void	ft_lstdel_env(t_env *lst);
int		check_oldpwd(t_paco *p);
void	restart_index(t_paco *p);

/*--- <PARSER> ---*/
int		parser_cmd(t_paco *p, int i);
void	get_cmd(t_paco *p, t_parser *node, int *i);
int		path_cmd(t_paco *p, t_parser *node);
int		p_utils(t_paco *p, t_parser *node, int *i);
int		check_builtin(t_paco *p);
void	exec_append(t_paco *p, t_parser *node, int *i);
void	exec_trunc(t_paco *p, t_parser *node, int *i);
void	read_only(t_paco *p, t_parser *node, int *i);
int		flag_pipe(t_paco *p, int *i);
void	exec_heredoc(t_paco *p, t_parser *node, int *i);
void	ft_heredoc(t_paco *p, char *limit);
void	pass_tokens(t_paco *p, int *k);

/*--- <TOKEN ERROR> ---*/
int		token_errors(t_paco *p, int *i);

/*--- <EXECUTER> ---*/
int		executer(t_paco *p, char **env, t_parser *node);
void	exec_father(t_paco *p, t_list *aux);
int		exec_child(t_paco *p, t_parser *node, t_list *aux, char **env);
void	exec_cmd2(t_paco *p, char **env, t_parser *node);

/*--- <EXECUTER ERROR> ---*/
int		exec_errors(t_paco *p, t_parser *node, t_list *aux);
int		msg_err(char *str);

/*--- <SIGNALS> ---*/
void	signals(int sig);
void	cat_ctrlbackslash(int sig);
void	cat_ctrlc(int sig);

/*--- <FREE MINISHELL> ---*/
void	free_mini_split(char **s, int j);
void	free_lex(t_paco *p);
void	free_lex2(t_paco *p);
void	free_all(t_paco *p);
void	free_path(t_paco *p);
void	free_split(char **tmp);
void	free_cd_error(t_paco *p);
void	free_cmd_list(t_list **lst);

#endif