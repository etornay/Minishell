/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:00:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/06 18:23:16 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//hay que usar un array de fd de dos int para poder abrir fd 0 y fd 1 con el dup2
int	exec_father(t_paco *p, t_parser *node, t_list *aux)
{
	if (aux->next && !((t_parser *)aux->next->content)->infile)
		((t_parser *)aux->next->content)->infile = p->fd[0];
	else
		close(p->fd[0]); //en caso de que fd[0] tenga algun valor se desactiva para ejecutar el proceso hijo
	close(p->fd[1]);
	waitpid(p->pid, &p->wait, 0);
}//PROCESO PADRE

int	exec_child(t_paco *p, t_parser *node, t_list *aux, char **env)
{
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (/*error dup infile*/, EXIT_FAILURE);
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDIN_FILENO) == -1)
			return (/*error dup outfile*/, EXIT_FAILURE);
		close(node->outfile);
	}
	else if (aux->next != NULL)
	{
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			return (/*error dup pipe out*/, EXIT_FAILURE);
	}
	close(p->fd[0]);
	close(p->fd[1]); /*CERRAR LOS FD USADOS EN EL PROCESO CON PIPE*/
	execve(node->full_path, node->full_cmd, env);
	exit(/*status FINAL DEL PROCESO CON PIPES*/);
}//PROCESO HIJO

void	exec_cmd2(t_paco *p, char **env, t_parser *node)
{
	if (p->heredoc_flag)
		dup2(p->heredoc_tmp, STDIN_FILENO);
	else
		dup2(node->infile, STDIN_FILENO);
	if (node->outfile != STDOUT_FILENO)
		dup2(node->outfile, STDOUT_FILENO);
	if (p->heredoc_flag)
		unlink("here_doc.tmp");
	execve(node->full_path, node->full_cmd, env);
}

int	exec_errors(t_paco *p, t_parser *node, t_list *aux)
{
	if (node->full_path == NULL)
		return (/*error de cmd 127*/);
	if (node->infile == -1 || node->outfile == -1)
	{
		if (p->lex2[0][0] == '<' || p->lex2[0][0] == '>')
			/*IMPRIMIR ERROR DE VOLCADO DE INFORMACION*/;
		else
			/*IMPRIMIR ERROR DE VOLCADDO*/;
		aux = aux->next;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}//ESTO A LO MEJOR NO SE PUEDE DEJAR ASI POR SISTEMA DE RUTAS DE ERROR
