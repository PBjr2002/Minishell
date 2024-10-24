/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:50:50 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 17:08:59 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	ft_fill_tree2_finisher(t_token *token_list,
		t_tree *current, int pipeline)
{
	while (token_list)
	{
		current = ft_fill_tree2_assist(token_list, current, pipeline);
		ft_fill_tree2_assist2(token_list, current, pipeline);
		if (token_list->type == TYPE_PIPE)
			break ;
		token_list = token_list->next;
	}
}

t_tree	*ft_redirect_branch_attach1_assist2(t_tree *tree, t_tree *new)
{
	if (tree->parent)
		new->parent = tree->parent;
	if (tree->parent)
		tree->parent->right = new;
	new->left = tree;
	tree->parent = new;
	return (new);
}

t_tree	*ft_redirect_branch_attach1_assist3(t_tree *tree, t_tree *new)
{
	new->parent = tree;
	tree->left->parent = new;
	new->left = tree->left;
	tree->left = new;
	return (tree);
}

t_tree	*ft_redirect_branch_attach1_assist4(t_tree *tree, t_tree *new)
{
	tree->parent = new;
	new->left = tree;
	return (new);
}
