/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:59:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/01 11:28:59 by pauberna         ###   ########.fr       */
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
	av = ft_calloc(sizeof(char *), av_len + 1);
	if (!av)
		return (NULL);
	if (build_av_helper(cmd, tree, tmp, av) == 1)
		return (free_env(av), NULL);
	return (av);
}

int	build_av_helper(t_tree *cmd, t_tree *tree, t_tree *tmp, char **av)
{
	int	len;

	len = 1;
	if (cmd)
	{
		av[0] = ft_strdup(cmd->str);
		if (!av[0])
			return (1);
	}
	if (tree)
	{
		while (tree)
		{
			av[len] = ft_strdup(tree->str);
			if (!av[len])
				return (1);
			len++;
			tree = tree->right;
		}
		tree = tmp;
	}
	av[len] = NULL;
	return (0);
}

void	tree_cleaner(t_tree *tree)
{
	if (!tree)
		return ;
	tree_cleaner(tree->left);
	tree_cleaner(tree->right);
	if (tree->str)
		free(tree->str);
	free(tree);
}

void	token_cleaner(t_token *token_list)
{
	if (token_list && token_list->next)
		token_cleaner(token_list->next);
	if (token_list)
	{
		if (token_list->str)
		{
			free(token_list->str);
			token_list->str = NULL;
		}
		free(token_list);
	}
}

void	fd_closer(t_tree *tree, t_tree *og, int mode)
{
	t_tree	*tmp;

	if (!tree)
		return ;
	tmp = NULL;
	if (mode == 0)
	{
		tmp = tree;
		while (tree->parent)
			tree = tree->parent;
		if (tree->right)
			fd_closer(tree->right, tmp, 1);	
		if (tree->left)
			fd_closer(tree->left, tmp, 1);
		og = tmp;
	}
	if (tree == og)
	{
		if (tree->right)
			fd_closer(tree->right, og, 1);
		if (tree->left)
			fd_closer(tree->left, og, 1);
		return ;
	}
	if (tree->right)
		fd_closer(tree->right, og, 1);
	if (tree->left)
		fd_closer(tree->left, og, 1);
	if (og)
	{
		if (tree->fd_in != STDIN_FILENO && tree->fd_in != og->fd_in)
			close(tree->fd_in);
		if (tree->fd_out != STDOUT_FILENO && tree->fd_out != og->fd_out)
			close(tree->fd_out);
	}
	if (mode == 2)
	{
		if (tree->fd_in != STDIN_FILENO)
			close(tree->fd_in);
		if (tree->fd_out != STDOUT_FILENO)
			close(tree->fd_out);
	}
	
}
