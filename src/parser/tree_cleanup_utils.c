/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:06:39 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/07 16:18:44 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//just a simple function, to save space, if syntax error, status = 2
t_environment	*tree_cleanup_function(t_tree *treetop, t_environment *info)
{
	//t_tree *temp;

	//temp = treetop;
	if (check_valid_pipes(treetop) == -1)
		info->status = 2;
	else if (check_valid_redirects(treetop) == -1)
		info->status = 2;
	return (info);
}

//checks to see if pipes have commands attached to them, to avoid segfaults
//without my intention, it also checks if commands are present if a pipeless input is sent...
int check_valid_pipes(t_tree *treetop)
{
	t_tree *temp;

	temp = treetop;
	if (treetop->type != TYPE_PIPE)
	{
		if (treetop->type != TYPE_COMMAND && (treetop->type != SINGLE_IN && treetop->type != SINGLE_OUT
			&& treetop->type != DOUBLE_IN && treetop->type != DOUBLE_OUT))
		{
			ft_printf("bingo bango bongo\n");
			return (-1);
		}
	}
	while (treetop->type == TYPE_PIPE)
	{
		if (!treetop->right || treetop->right->type != TYPE_COMMAND)
			return (-1);
		if (treetop->left && treetop->left->type == TYPE_PIPE)
			treetop = treetop->left;
		else
			break;
	}
	if (temp->type == TYPE_PIPE && treetop->left && treetop->left->type != TYPE_COMMAND)
		return (-1);
	return (0);
}


//runs the tree to setup check_valid_redirects2
int check_valid_redirects(t_tree *treetop)
{
	while (treetop)
	{
		if (treetop->right && treetop->right->type == TYPE_COMMAND)
		{
			if (check_valid_redirects_2(treetop->right) == -1)
				return (-1);
		}
		if (treetop->left && treetop->left->type == TYPE_COMMAND)
		{
			if (check_valid_redirects_2(treetop->left) == -1)
				return (-1);
		}
		if (treetop->type == TYPE_COMMAND)
		{
			if (check_valid_redirects_2(treetop) == -1)
				return (-1);
		}
		if (treetop->left && treetop->left->type == TYPE_PIPE)
		{
			treetop = treetop->left;
			continue ;
		}
		return (0);
	}
	return (0);
}
// checks the current command for valid redirections
int check_valid_redirects_2(t_tree *treetop)
{
	while (treetop && treetop->left)
	{
		if (treetop->left->type == SINGLE_IN || treetop->left->type == SINGLE_OUT
			|| treetop->left->type == DOUBLE_IN || treetop->left->type == DOUBLE_OUT)
		{
			if (!treetop->left->str)
				return (-1);
		}
		if (treetop->left)
			treetop = treetop->left;
	}
	return (0);
}