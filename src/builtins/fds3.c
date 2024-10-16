/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:16:39 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/16 13:35:10 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_fds_helper(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else if (tree->left->fd_in != 0)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->parent->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else
		{
			if (dup2(tree->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
	}
	else if (dup2(tree->fd_in, STDIN_FILENO) == -1
		|| dup2(tree->parent->fd_out, STDOUT_FILENO) == -1)
		exec_exit(envr->status, 0, 1);
}

void	set_fds_helper2(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else if (tree->left->fd_in != 0)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->parent->parent->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else
		{
			if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
	}
	else if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1
		|| dup2(tree->parent->parent->fd_out, STDOUT_FILENO) == -1)
		exec_exit(envr->status, 0, 1);
}

void	set_fds_helper3(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else if (tree->left->fd_in != 0)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else
		{
			if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
	}
	else if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1
		|| dup2(tree->fd_out, STDOUT_FILENO) == -1)
		exec_exit(envr->status, 0, 1);
}

void	set_fds_helper4(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else if (tree->left->fd_in != 0)
		{
			if (dup2(tree->left->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
		else
		{
			if (dup2(tree->fd_in, STDIN_FILENO) == -1
				|| dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
				exec_exit(envr->status, 0, 1);
		}
	}
	else if (dup2(tree->fd_in, STDIN_FILENO) == -1
		|| dup2(tree->fd_out, STDOUT_FILENO) == -1)
		exec_exit(envr->status, 0, 1);
}
