/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/16 17:30:54 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decider(t_tree *tree, t_environment *envr)
{
	t_tree	*tmp;

	tmp = tree;
	if (ft_strcmp(tree->str, "echo") == 0)
	{
		tree = tree->right;
		exec_echo(tree, tmp, envr);
	}
	else if (ft_strcmp(tree->str, "cd") == 0)
		exec_cd(fd, av, info);
	else if (ft_strcmp(tree->str, "pwd") == 0)
		exec_pwd(fd);
	else if (ft_strcmp(tree->str, "export") == 0)
		exec_export(fd, av, info);
	else if (ft_strcmp(tree->str, "env") == 0)
		exec_env(fd, info);
	else if (ft_strcmp(tree->str, "exit") == 0)
		prepare_exit(av, info);
	else if (ft_strcmp(tree->str, "unset") == 0)
		exec_unset(av, info);
	else
		exec_other(fd, av, info);
}

void	search_tree(t_tree *tree, t_environment *envr)
{
	t_tree	*tmp;

	while (tree)
	{
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
					redirect_solver(tree, tmp);
					tree->solved = true;
					tree = tree->parent;
				}
			}
			decider(tree);
			tree->solved = true;
		}
		tree = tree->parent;
	}
}

void	redirect_solver(t_tree *tree, t_tree *cmd)
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
	if (dup2(tree->fd_in, cmd->fd_in) == -1)
		printf("There was an error redirecting\n");
	if (dup2(tree->fd_out, cmd->fd_out) == -1)
		printf("There was an error redirecting\n");
}
