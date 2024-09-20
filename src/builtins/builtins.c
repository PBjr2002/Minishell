/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/20 13:08:00 by pauberna         ###   ########.fr       */
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

void	search_tree(t_tree *tree, t_environment *envr)
{
	t_tree	*tmp;

	if (tree->left && tree->left->solved == false)
	{
		search_tree(tree->left, envr);
		redirect_solver(tree);
	}
	else if (tree->right && tree->type == TYPE_COMMAND)
	{
		tmp = tree;
		if (tree->right)
			tree = tree->right;
		decider(tree, tmp, envr);
	}
	else
		decider(NULL, tree, envr);
	tree->solved = true;
	/* while (tree)
	{
		//recursividade
		while (tree && tree->type != 8 && tree->type != 10)
			tree = tree->left;
		if (tree)
		{
			tmp = tree;
			if (tree->left)
			{
				while (tree->left)
					tree = tree->left;
				while (tree != tmp)
				{
					redirect_solver(tree);
					tree->solved = true;
					tree = tree->parent;
				}
			}
			decider(tree, envr);
			tree->solved = true;
		}
		tree = tree->parent;
	} */
}

void	redirect_solver(t_tree *tree)
{
	if (tree->type == SINGLE_IN)
		tree->fd_in = open(tree->str, O_TRUNC);
	else if (tree->type == SINGLE_OUT)
		tree->fd_out = open(tree->str, O_TRUNC);
	else if (tree->type == DOUBLE_IN)
		tree->fd_in = open(tree->str, O_APPEND);
	else if (tree->type == DOUBLE_OUT)
		tree->fd_out = open(tree->str, O_APPEND);
	if (tree->fd_in == -1 || tree->fd_out == -1)
		printf("There was an error opening\n");
	if (dup2(tree->fd_in, STDIN_FILENO) == -1)
		printf("There was an error redirecting\n");
	if (dup2(tree->fd_out, STDOUT_FILENO) == -1)
		printf("There was an error redirecting\n");
	tree->solved = true;
}
