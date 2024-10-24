/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:40:05 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/23 14:59:52 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_single_in(t_tree *tree, int write)
{
	tree->fd_in = open(tree->str, O_RDONLY | O_APPEND, 0644);
	if (tree->left && tree->left->fd_out != 1)
	{
		tree->fd_out = tree->left->fd_out;
		if (tree->fd_out == -1)
			return (-1);
		return (3);
	}
	if (tree->fd_in == -1)
	{
		if (write == 0)
			printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	return (2);
}

int	redirect_single_out(t_tree *tree, int write)
{
	tree->fd_out = open(tree->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tree->left && tree->left->fd_in != 0)
	{
		tree->fd_in = tree->left->fd_in;
		if (tree->fd_in == -1)
			return (-1);
		return (3);
	}
	if (tree->fd_out == -1)
	{
		if (write == 0)
			printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	return (1);
}

int	redirect_double_in(t_tree *tree, t_environment *envr)
{
	if (tree->solved == true)
	{
		if (tree->left && (tree->left->type == SINGLE_OUT
				|| tree->left->type == DOUBLE_OUT))
			tree->fd_out = tree->left->fd_out;
		return (2);
	}
	tree->fd_in = exec_here_doc(tree, envr);
	if (tree->fd_in == -2)
	{
		tree->solved = true;
		return (-2);
	}
	if (tree->left && tree->left->fd_out != 1)
	{
		tree->fd_out = tree->left->fd_out;
		if (tree->fd_out == -1)
			return (-1);
		return (3);
	}
	return (2);
}

int	redirect_double_out(t_tree *tree, int write)
{
	tree->fd_out = open(tree->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tree->left && tree->left->fd_in != 0)
	{
		tree->fd_in = tree->left->fd_in;
		if (tree->fd_in == -1)
			return (-1);
		return (3);
	}
	if (tree->fd_out == -1)
	{
		if (write == 0)
			printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	tree->solved = true;
	return (1);
}
