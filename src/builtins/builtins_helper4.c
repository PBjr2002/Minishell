/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:59:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/18 13:47:00 by lmiguel-         ###   ########.fr       */
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
	char	*stmp;
	int		len;

	len = 1;
	stmp = NULL;
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
			if (build_av_helper2(tree, av, stmp, len) == 1)
				return (1);
			len++;
			if (tree)
				tree = tree->right;
		}
		tree = tmp;
	}
	av[len] = NULL;
	return (0);
}

int	build_av_helper2(t_tree *tree, char **av, char *stmp, int len)
{
	if (tree->right && tree->right->append_before == true)
	{
		while (tree->right && tree->right->append_before == true)
		{
			if (av[len])
			{
				stmp = ft_strdup(av[len]);
				free(av[len]);
			}
			else
				stmp = ft_strdup(tree->str);
			av[len] = ft_strjoin(stmp, tree->right->str);
			free(stmp);
			tree = tree->right;
		}
		tree = tree->right;
	}
	else
		av[len] = ft_strdup(tree->str);
	if (!av[len])
		return (1);
	return (0);
}

void	tree_cleaner(t_tree *tree, int mode)
{
	if (!tree)
		return ;
	if (mode == 0)
	{
		while (tree->parent)
			tree = tree->parent;
	}
	tree_cleaner(tree->left, 1);
	tree_cleaner(tree->right, 1);
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
