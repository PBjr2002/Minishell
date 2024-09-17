/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:52:11 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/17 15:41:59 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//This includes functions to add additional branches to a tree or nodes to a list. branch_type 1 for left, 2 for right
t_tree	*ft_pipe_branch_attach(t_tree *tree, t_tree *new)
{
	tree->parent = new;
	new->left = tree;
	new->pipeline = new->pipeline + 1;
	return (new);
}

// this attaches redirect branches to our current tree pointer, hopefully a pipe, a command or another redirection
void	ft_redirect_branch_attach1(t_tree *tree, t_tree *new)
{
	if (tree->left == NULL)
	{
		new->parent = tree;
		tree->left = new;
	}
	else
	{
		tree->left->parent = new;
		new->left = tree->left;
		tree->left = new;
		new->parent = tree;
	}
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
		new->right = tree->right;
		tree->right = new;
		new->parent = tree;
	}
}

// this attaches command branches atop a redirection, only called when no pipes exist
t_tree	*ft_command_branch_attach_zero(t_tree *tree, t_tree *new)
{
	tree->parent = new;
	new->left = tree;
	return (new);
}

// this attaches command branches, hopefully only to pipes and only on the left side (please)
void	ft_command_branch_attach1(t_tree *tree, t_tree *new)
{
	if (tree->left == NULL)
	{
		new->parent = tree;
		tree->left = new;
	}
	else
	{
		tree->left->parent = new;
		new->left = tree->left;
		tree->left = new;
		new->parent = tree;
	}
}

// this attaches command branches, hopefully only to pipes and only on the right side (please)
void	ft_command_branch_attach2(t_tree *tree, t_tree *new)
{
	if (tree->right == NULL)
	{
		new->parent = tree;
		tree->right = new;
	}
	else
	{
		tree->right->parent = new;
		new->right = tree->right;
		tree->right = new;
		new->parent = tree;
	}
}

//this attaches argument branches, hopefully only to commands and only on the left side
void	ft_argument_branch_attach(t_tree *tree, t_tree *new)
{
	if (tree->right == NULL)
	{
		new->parent = tree;
		tree->right = new;
	}
	else
	{
		tree->right->parent = new;
		new->right = tree->right;
		tree->right = new;
		new->parent = tree;
	}
}

// exactly what it says, appends a token to an existing token list
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
