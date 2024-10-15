/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/15 16:55:52 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	decider(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	set_builtins_fds(cmd);
	if (ft_strcmp(cmd->str, "echo") == 0 && tree)
		envr->status = exec_echo(tree, cmd, envr);
	else if (ft_strcmp(cmd->str, "cd") == 0)
		envr->status = exec_cd(tree, cmd, envr);
	else if (ft_strcmp(cmd->str, "pwd") == 0)
		envr->status = exec_pwd(cmd);
	else if (ft_strcmp(cmd->str, "export") == 0)
		envr->status = exec_export(tree, cmd, envr);
	else if (ft_strcmp(cmd->str, "env") == 0)
		envr->status = exec_env(cmd, envr);
	else if (ft_strcmp(cmd->str, "exit") == 0)
		prepare_exit(tree, cmd, envr);
	else if (ft_strcmp(cmd->str, "unset") == 0)
		envr->status = exec_unset(tree, envr);
	else
		exec_other(tree, cmd, envr);
	if (tree)
		tree->solved = true;
	else
		cmd->solved = true;
}

int	redirect_solver(t_tree *tree, t_environment *envr)
{
	int	mode;

	mode = -1;
	if (tree->type == SINGLE_IN)
		mode = redirect_single_in(tree);
	else if (tree->type == SINGLE_OUT)
		mode = redirect_single_out(tree);
	else if (tree->type == DOUBLE_IN)
		mode = redirect_double_in(tree, envr);
	else if (tree->type == DOUBLE_OUT)
		mode = redirect_double_out(tree);
	envr->fds++;
	return (mode);
}

void	pipe_setup(t_tree *tree)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	tree->fd_in = fd[0];
	tree->fd_out = fd[1];
}
