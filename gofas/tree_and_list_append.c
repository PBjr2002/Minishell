/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:52:11 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/22 13:53:08 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This includes functions to add additional branches to a tree or nodes to a list.

void	ft_branch_attach(t_tree *tree, t_tree *new, int branch_type)
{
	if (branch_type == 1)
	{
		new->parent = tree;
		tree->left = new;
		new->index = (tree->index + 1);
	}
	if (branch_type == 2)
	{
		new->parent = tree;
		tree->right = new;
		new->index = (tree->index + 1);
	}
}