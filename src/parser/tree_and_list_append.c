/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:52:11 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 17:04:58 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//This includes functions to add additional branches to a 
// tree or nodes to a list. branch_type 1 for left, 2 for right
t_tree	*ft_pipe_branch_attach(t_tree *tree, t_tree *new)
{
	tree->parent = new;
	new->left = tree;
	return (new);
}

// this attaches redirect branches to our current tree pointer, 
// hopefully a pipe, a command or another redirection
void	ft_redirect_branch_attach1(t_tree *tree, t_tree *new)
{
	if (tree->left == NULL)
	{
		if (tree->type == SINGLE_IN || tree->type == DOUBLE_IN \
		|| tree->type == SINGLE_OUT || tree->type == DOUBLE_OUT)
			ft_redirect_brach_attach1_assist(tree, new);
		else
		{
			new->parent = tree;
			tree->left = new;
		}
	}
	else
	{
		tree->left->parent = new;
		new->left = tree->left;
		tree->left = new;
		new->parent = tree;
	}
}

void	ft_redirect_brach_attach1_assist(t_tree *tree, t_tree *new)
{
	t_tree	*temp;

	temp = tree;
	if (tree->parent)
		tree->parent->right = new;
	tree = new;
	tree->left = temp;
	temp->parent = tree;
}

// this attaches redirect branches to the right side of the pipe
void	ft_redirect_branch_attach2(t_tree *tree, t_tree *new)
{
	if (tree->right == NULL)
	{
		new->parent = tree;
		tree->right = new;
	}
	else
	{
		tree->right->parent = new;
		tree->right = new;
		new->right = tree->right;
		new->parent = tree;
	}
}

// this attaches command branches atop a redirection, 
// only called when no pipes exist
t_tree	*ft_command_branch_attach_zero(t_tree *tree, t_tree *new,
		t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TYPE_COMMAND)
		{
			while (tree->parent)
				tree = tree->parent;
			tree->parent = new;
			new->left = tree;
			new->append_before = token_list->append_before;
		}
		token_list = token_list->next;
	}
	return (new);
}
