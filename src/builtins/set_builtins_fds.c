/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtins_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:30 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/17 17:33:45 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_builtins_fds(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_COMMAND)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE
			&& tree == tree->parent->left)
			set_builtins_fds_helper(tree);
		else if (tree->parent && tree->parent->type == TYPE_PIPE
			&& tree == tree->parent->right)
		{
			if (tree->parent->parent && tree->parent->parent->type == TYPE_PIPE)
				set_builtins_fds_helper2(tree);
			else
				set_builtins_fds_helper3(tree);
		}
		else
			set_builtins_fds_helper4(tree);
	}
}

void	set_builtins_fds_helper(t_tree *tree)
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

void	set_builtins_fds_helper2(t_tree *tree)
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

void	set_builtins_fds_helper3(t_tree *tree)
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

void	set_builtins_fds_helper4(t_tree *tree)
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
