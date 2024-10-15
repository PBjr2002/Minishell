/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/15 15:06:54 by pauberna         ###   ########.fr       */
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

void	set_builtins_fds(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_COMMAND)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE && tree == tree->parent->left)
		{
			if (tree->left)
			{
				if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
				{
					tree->fd_in = tree->left->fd_in;
					tree->fd_out = tree->left->fd_out;
				}
				else if (tree->left->fd_in != 0)
				{
					tree->fd_in = tree->left->fd_in;
					tree->fd_out = tree->parent->fd_out;
				}
				else
					tree->fd_out = tree->left->fd_out;
			}
			else
				tree->fd_out = tree->parent->fd_out;
		}
		else if (tree->parent && tree->parent->type == TYPE_PIPE && tree == tree->parent->right)
		{
			if (tree->parent->parent && tree->parent->parent->type == TYPE_PIPE)
			{
				if (tree->left)
				{
					if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
					{
						tree->fd_in = tree->left->fd_in;
						tree->fd_out = tree->left->fd_out;
					}
					else if (tree->left->fd_in != 0)
					{
						tree->fd_in = tree->left->fd_in;
						tree->fd_out = tree->parent->parent->fd_out;
					}
					else
					{
						tree->fd_in = tree->parent->fd_in;
						tree->fd_out = tree->left->fd_out;
					}
				}
				else
				{
					tree->fd_in = tree->parent->fd_in;
					tree->fd_out = tree->parent->parent->fd_out;
				}
			}
			else
			{
				if (tree->left)
				{
					if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
					{
						tree->fd_in = tree->left->fd_in;
						tree->fd_out = tree->left->fd_out;
					}
					else if (tree->left->fd_in != 0)
						tree->fd_in = tree->left->fd_in;
					else
					{
						tree->fd_in = tree->parent->fd_in;
						tree->fd_out = tree->left->fd_out;
					}
				}
				else
					tree->fd_in = tree->parent->fd_in;
			}
		}
		else
		{
			if (tree->left)
			{
				if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
				{
					tree->fd_in = tree->left->fd_in;
					tree->fd_out = tree->left->fd_out;
				}
				else if (tree->left->fd_in != 0)
					tree->fd_in = tree->left->fd_in;
				else
					tree->fd_out = tree->left->fd_out;
			}
		}
	}
}
