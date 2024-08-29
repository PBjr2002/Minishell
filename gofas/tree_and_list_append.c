/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:52:11 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/29 14:35:45 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This includes functions to add additional branches to a tree or nodes to a list. branch_type 1 for left, 2 for right
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

//exactly what it says, appends a token to an existing token list
void	ft_token_append(t_token *token_list, t_token *new, char *str)
{
	int index_num;

	index_num = -1;
	while (token_list->next != NULL)
	{
		index_num++;
		token_list = token_list->next;
	}
	token_list->next = new;
	new->previous = token_list;
	new->index = index_num + 1;
	new->str = str;
}
