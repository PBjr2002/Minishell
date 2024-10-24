/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:52:11 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 17:03:08 by lmiguel-         ###   ########.fr       */
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
t_tree	*ft_redirect_branch_attach1(t_tree *tree, t_tree *new)
{
	if (tree->left == NULL && tree->pipeline < 2)
	{
		if (tree->type == SINGLE_IN || tree->type == DOUBLE_IN \
		|| tree->type == SINGLE_OUT || tree->type == DOUBLE_OUT)
		{
			tree = ft_redirect_branch_attach1_assist(tree, new);
			return (tree);
		}
		else
		{
			new->parent = tree;
			tree->left = new;
			return (tree);
		}
	}
	else
	{
		if (tree->pipeline > 1)
			return (ft_redirect_branch_attach1_assist2(tree, new));
		if (tree->pipeline == 1)
			return (ft_redirect_branch_attach1_assist3(tree, new));
		else
			return (ft_redirect_branch_attach1_assist4(tree, new));
	}
}

t_tree	*ft_redirect_branch_attach1_assist(t_tree *tree, t_tree *new)
{
	t_tree	*temp;

	temp = tree;
	if (tree->parent && tree->pipeline > 1)
	{
		tree->parent->right = new;
		new->parent = tree->parent;
	}
	else if (tree->parent)
	{
		tree->parent->left = new;
		new->parent = tree->parent;
	}
	tree = new;
	tree->left = temp;
	temp->parent = tree;
	return (tree);
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
