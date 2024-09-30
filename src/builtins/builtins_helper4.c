/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:59:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/30 17:32:33 by pauberna         ###   ########.fr       */
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

void	fd_closer(t_tree *tree, int mode)
{
	int	i;

	if (!tree)
		return ;
	if (mode == 0)
	{
		i = 3;
		while (i < FOPEN_MAX)
		{
			if (i != STDIN_FILENO && i != STDOUT_FILENO)
				close(i);
			i++;
		}
	}
}
