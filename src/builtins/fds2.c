/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:36:35 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/15 17:44:42 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds_helper(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
			close_specific_fds(envr, tree->left->fd_in, tree->left->fd_out);
		else if (tree->left->fd_in != 0)
			close_specific_fds(envr, tree->left->fd_in, tree->parent->fd_out);
		else
			close_specific_fds(envr, tree->fd_in, tree->left->fd_out);
	}
	else
		close_specific_fds(envr, tree->fd_in, tree->parent->fd_out);
}

void	close_fds_helper2(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
			close_specific_fds(envr, tree->left->fd_in, tree->left->fd_out);
		else if (tree->left->fd_in != 0)
			close_specific_fds(envr, tree->left->fd_in,
				tree->parent->parent->fd_out);
		else
			close_specific_fds(envr, tree->parent->fd_in, tree->left->fd_out);
	}
	else
		close_specific_fds(envr, tree->parent->fd_in,
			tree->parent->parent->fd_out);
}

void	close_fds_helper3(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
			close_specific_fds(envr, tree->left->fd_in, tree->left->fd_out);
		else if (tree->left->fd_in != 0)
			close_specific_fds(envr, tree->left->fd_in, tree->fd_out);
		else
			close_specific_fds(envr, tree->parent->fd_in, tree->left->fd_out);
	}
	else
		close_specific_fds(envr, tree->parent->fd_in, tree->fd_out);
}

void	close_fds_helper4(t_tree *tree, t_environment *envr)
{
	if (tree->left)
	{
		if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
			close_specific_fds(envr, tree->left->fd_in, tree->left->fd_out);
		else if (tree->left->fd_in != 0)
			close_specific_fds(envr, tree->left->fd_in, tree->fd_out);
		else
			close_specific_fds(envr, tree->fd_in, tree->left->fd_out);
	}
	else
		close_specific_fds(envr, tree->fd_in, tree->fd_out);
}
