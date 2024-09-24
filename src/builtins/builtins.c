/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/24 15:43:17 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	decider(t_tree *tree, t_tree *cmd, t_environment *envr)
{
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

void	search_tree(t_tree *tree, t_environment *envr, int mode)
{
	t_tree	*tmp;

	if (tree->type == 1 || tree->type == 2 || tree->type == 3
		|| tree->type == 4 || tree->type == 5 || tree->type == 9)
		expand_everything(tree, envr);
	if (tree->type == TYPE_COMMAND && tree->left)
		mode = search_redirect(tree, envr);
	search_pipe(tree, envr);
	if (tree->right && tree->type == TYPE_COMMAND)
	{
		fd_setup(tree, mode);
		tmp = tree;
		if (tree->right)
			tree = tree->right;
		decider(tree, tmp, envr);
	}
	else
	{
		if (tree->type != TYPE_PIPE)
		{
			fd_setup(tree, mode);
			decider(NULL, tree, envr);
		}
	}
	tree->solved = true;
}

int	redirect_solver(t_tree *tree, t_environment *envr)
{
	if (tree->type == SINGLE_IN)
	{
		tree->fd_in = open(tree->str, O_RDONLY | O_TRUNC, 0644);
		if (tree->left && (tree->left->type == SINGLE_OUT
				|| tree->left->type == DOUBLE_OUT))
			tree->fd_out = tree->left->fd_out;
	}
	else if (tree->type == SINGLE_OUT)
	{
		tree->fd_out = open(tree->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (tree->left && tree->left->type == SINGLE_IN)
			tree->fd_in = tree->left->fd_in;
	}
	else if (tree->type == DOUBLE_IN)
		tree->fd_in = exec_here_doc(tree, envr);
	else if (tree->type == DOUBLE_OUT)
	{
		tree->fd_out = open(tree->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (tree->left && tree->left->type == SINGLE_IN)
			tree->fd_in = tree->left->fd_in;
	}
	if (tree->fd_in == -1 || tree->fd_out == -1)
		printf("There was an error opening\n");
	tree->solved = true;
	return (3);
}

void	pipe_setup(t_tree *tree)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	tree->fd_in = fd[0];
	tree->fd_out = fd[1];
}

void	fd_setup(t_tree *tree, int mode)
{
	if (tree->left && (tree->left->type == 1 || tree->left->type == 2
			|| tree->left->type == 3 || tree->left->type == 4))
	{
		tree->fd_in = tree->left->fd_in;
		tree->fd_out = tree->left->fd_out;
	}
	else if (tree->parent && tree->parent->type == TYPE_PIPE)
	{
		if (mode == 1)
			tree->fd_out = tree->parent->fd_out;
		else if (mode == 2)
			tree->fd_in = tree->parent->fd_in;
		else if (mode == 3)
		{
			tree->fd_in = tree->parent->fd_in;
			tree->fd_out = tree->parent->parent->fd_out;
		}
	}
}
