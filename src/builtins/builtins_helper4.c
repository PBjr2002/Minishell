/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:59:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/22 18:52:46 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**build_av(t_tree *tree, t_tree *cmd)
{
	t_tree	*tmp;
	char	**av;
	int		av_len;

	av_len = 0;
	if (cmd)
		av_len++;
	if (tree)
	{
		tmp = tree;
		while (tree)
		{
			av_len++;
			tree = tree->right;
		}
		tree = tmp;
	}
	av = ft_calloc(sizeof(char*), av_len + 1);
	if (!av)
		return (NULL);
	if (cmd)
		av[0] = ft_strdup(cmd->str);
	if (tree)
	{
		av_len = 1;
		while (tree)
		{
			av[av_len] = ft_strdup(tree->str);
			av_len++;
			tree = tree->right;
		}
		av[av_len] = NULL;
		tree = tmp;
	}
	return (av);
}

void	tree_cleaner(t_tree *tree)
{
	if (tree->left)
		tree_cleaner(tree->left);
	if (tree->right)
		tree_cleaner(tree->right);
	if (tree->str)
	{
		free(tree->str);
		tree->str = NULL;
	}
	if (tree)
	{
		free(tree);
		tree = NULL;
	}
}

void	token_cleaner(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		free(token_list->str);
		tmp = token_list->next;
		free(token_list);
		token_list = tmp;
	}
}

void	fd_closer(t_tree *tree, int mode)
{
	if (!tree)
		return ;
	if (mode == 0)
	{
		while (tree->parent)
			tree = tree->parent;
		if (tree->right)
			fd_closer(tree->right, 1);
		if (tree->left)
			fd_closer(tree->left, 1);
	}
	if (tree->right)
		fd_closer(tree->right, 1);
	if (tree->left)
		fd_closer(tree->left, 1);
	if (tree->fd_in != STDIN_FILENO && tree->fd_in != STDOUT_FILENO
		&& tree->fd_in != STDERR_FILENO)
		close(tree->fd_in);
	if (tree->fd_out != STDIN_FILENO && tree->fd_out != STDOUT_FILENO
		&& tree->fd_out != STDERR_FILENO)
		close(tree->fd_out);
}
