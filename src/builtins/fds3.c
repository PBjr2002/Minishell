/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:16:39 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/22 18:47:11 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_fds_helper(t_tree *tree, int *fd)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
		else if (tree->left->fd_in != 0)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->parent->fd_out, STDOUT_FILENO);
		}
		else
		{
			fd[0] = dup2(tree->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
	}
	else
	{
		fd[0] = dup2(tree->fd_in, STDIN_FILENO);
		fd[1] = dup2(tree->parent->fd_out, STDOUT_FILENO);
	}
}

void	set_fds_helper2(t_tree *tree, int *fd)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
		else if (tree->left->fd_in != 0)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->parent->parent->fd_out, STDOUT_FILENO);
		}
		else
		{
			fd[0] = dup2(tree->parent->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
	}
	else
	{
		fd[0] = dup2(tree->parent->fd_in, STDIN_FILENO);
		fd[1] = dup2(tree->parent->parent->fd_out, STDOUT_FILENO);
	}
}

void	set_fds_helper3(t_tree *tree, int *fd)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
		else if (tree->left->fd_in != 0)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->fd_out, STDOUT_FILENO);
		}
		else
		{
			fd[0] = dup2(tree->parent->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
	}
	else
	{
		fd[0] = dup2(tree->parent->fd_in, STDIN_FILENO);
		fd[1] = dup2(tree->fd_out, STDOUT_FILENO);
	}
}

void	set_fds_helper4(t_tree *tree, int *fd)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
		else if (tree->left->fd_in != 0)
		{
			fd[0] = dup2(tree->left->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->fd_out, STDOUT_FILENO);
		}
		else
		{
			fd[0] = dup2(tree->fd_in, STDIN_FILENO);
			fd[1] = dup2(tree->left->fd_out, STDOUT_FILENO);
		}
	}
	else
	{
		fd[0] = dup2(tree->fd_in, STDIN_FILENO);
		fd[1] = dup2(tree->fd_out, STDOUT_FILENO);
	}
}
