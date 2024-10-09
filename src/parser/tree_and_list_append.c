/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:52:11 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/09 14:00:21 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//This includes functions to add additional branches to a tree or nodes to a list. branch_type 1 for left, 2 for right
t_tree	*ft_pipe_branch_attach(t_tree *tree, t_tree *new)
{
	tree->parent = new;
	new->left = tree;
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
	//printf("whoop\n");
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
t_tree	*ft_command_branch_attach_zero(t_tree *tree, t_tree *new, t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TYPE_COMMAND)
		{
			tree->parent = new;
			new->left = tree;
			new->append_before = token_list->append_before;
		}	
		token_list = token_list->next;
	}
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
		if (tree->right->type == SINGLE_IN || tree->right->type == SINGLE_OUT 
		|| tree->right->type == DOUBLE_IN || tree->right->type == DOUBLE_OUT)
		{
			tree->right->parent = new;
			new->left = tree->right;
			tree->right = new;
			new->parent = tree;
		}
		else
		{
			tree->right->parent = new;
			new->right = tree->right;
			tree->right = new;
			new->parent = tree;
		}
	}
}

//this attaches argument branches, hopefully only to commands and only on the right side
void	ft_argument_branch_attach(t_tree *tree, t_tree *new)
{
	t_tree	*tmp;
	
	if (tree->right == NULL)
	{
		new->parent = tree;
		tree->right = new;
	}
	else
	{
		tmp = tree;
		while (tree->right)
			tree = tree->right;
		tree->right = new;
		new->parent = tree;
		tree = tmp;
	}
//n sei se era o suposto mas os argumentos estavam a sair na ordem errada então corrigi
//fixed, estavam na ordem correta
	
		/* tree->right->parent = new;
		new->right = tree->right;
		tree->right = new;
		new->parent = tree; */
}

// exactly what it says, appends a token to an existing token list
void	ft_token_append(t_token *token_list, t_token *new, char *str)
{
	int index_num;

	index_num = -1;
	(void) str;
	while (token_list->next != NULL)
	{
		index_num++;
		token_list = token_list->next;
	}
	token_list->next = new;
	new->previous = token_list;
	new->index = index_num + 1;
	//new->str = str;
}

// this adds a token to the middle of the token list
void	midlist_token_append(t_token *token_list, t_token *new)
{
	int index_num;

	index_num = -1;
	while (token_list->next != NULL && index_num != new->index)
	{
		index_num++;
		token_list = token_list->next;
	}
	new->next = token_list->next;
	new->previous = token_list;
	if (token_list->next)
		token_list->next->previous = new;
	token_list->next = new;
	new->index = token_list->index + 1;
	token_list = new;
	token_list->type = TYPE_ARGUMENT;
	if (token_list->next)
	{
		while (token_list)
		{
			token_list->index = token_list->index + 1;
			token_list = token_list->next;
		}
	}
}
