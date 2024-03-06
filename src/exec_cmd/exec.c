/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:38:55 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/06 18:26:43 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtins(t_parser *node, t_paco *p)
{
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "pwd\0", 4) == EXIT_SUCCESS)
		exec_pwd(p);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "env\0", 4) == EXIT_SUCCESS)
		exec_env(p);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "export\0", 7) == EXIT_SUCCESS)
		exec_export(p, p->lex2, 1);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "unset\0", 6) == EXIT_SUCCESS)
		exec_unset(p, p->lex2[1]);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "echo\0", 5) == EXIT_SUCCESS)
		flag_echo(p->lex2, 0, p);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "cd\0", 3) == EXIT_SUCCESS)
		exec_cd(p, p->lex2, 0);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "exit\0", 5) == EXIT_SUCCESS)
	{
		free_path(p);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	exec_cmd(t_paco *p, char **env)
{
	t_parser	*node;
	t_list		*aux;

	aux = p->lst_cmd;
	while (aux)
	{
		node = ((t_parser *)aux->content);
		if (exec_error(p, node) == EXIT_FAILURE)
			continue ;
		p->pid = fork();
		if (p->pid == -1)
			return (EXIT_FAILURE);
		if (p->pid == 0)
			exec_cmd2(p, env, node);
		else
			waitpid(p->pid, &p->wait, 0);
		aux = aux->next;
	}
	if (p->heredoc_flag)
		unlink("here_doc.tmp");
	return (EXIT_SUCCESS);
}

static int	exec_pipe_cmd(t_paco *p, char **env)
{
	t_parser	*node;
	t_list		*aux;

	aux = p->lst_cmd;
	while (aux)
	{
		node = ((t_parser *)aux->content);
		if (exec_error(p, node) == EXIT_FAILURE)
			continue ; //esto se tendra que cambiar
		if (pipe(p->fd) == -1)
			return (/*error pipe cmds*/);
		p->pid = fork();
		if (p->pid == -1)
		{
			close(p->fd[0]);
			close(p->fd[1]);
			return (/*error fork cmds*/);
		}
		if (p->pid == 0)
			if (exec_child(p, node, aux, env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		else
			exec_father(p, node, aux);
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}

int	executer(t_paco *p, char **env)
{
	if (p->lst_cmd && ((t_parser *)p->lst_cmd->content)->full_cmd
		&& ((t_parser *)p->lst_cmd->content)->full_cmd[0]
		&& ((t_parser *)p->lst_cmd->content)->full_path[0] == NULL) //probablemente hay que usar el check builtins
		/*status =*/exec_builtins(p->lst_cmd, p);
	else if (p->lst_cmd && ((t_parser *)p->lst_cmd->content)->full_cmd
		&& ((t_parser *)p->lst_cmd->content)->full_cmd[0]
		&& ((t_parser *)p->lst_cmd->content)->full_path[0] != NULL)//probablemente hay que usar el check builtins
	{
		if (p->pipe_flag)
			/*status =*/exec_pipe_cmd(p, env);
		else if (!p->pipe_flag)
			/*status =*/exec_cmd(p, env);
	}
	else if (p->lst_cmd && !((t_parser *)p->lst_cmd->content)->full_cmd
		&& !((t_parser *)p->lst_cmd->content)->full_path)
		return (/*status,*/EXIT_SUCCESS);
	else
	{
		if (p->lst_cmd && !((t_parser *)p->lst_cmd->content)->full_cmd)
			/*error de cmd 127*/
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
