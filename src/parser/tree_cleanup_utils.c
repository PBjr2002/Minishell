/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:06:39 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 15:33:43 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//just a simple function, to save space, if syntax error, status = 2

t_environment	*tree_cleanup_function(t_tree *treetop, t_environment *info)
{
	t_tree	*tmp;

	tmp = treetop;
	if (check_valid_pipes(treetop, tmp) == -1)
		info->status = 2;
	else if (check_valid_redirects(tmp) == -1)
		info->status = 2;
	else
	{
		info->old_status = info->status;
		info->status = 0;
	}
	return (info);
}

//checks to see if pipes have commands attached to them, to avoid segfaults
//without my intention, it also checks
//if commands are present if a pipeless input is sent...
int	check_valid_pipes(t_tree *treetop, t_tree *temp)
{
	temp = treetop;
	if (treetop->type != TYPE_PIPE)
	{
		if (syntax_checker_assist1(treetop, 1) == -1)
			return (-1);
	}
	while (treetop->type == TYPE_PIPE)
	{
		if (syntax_checker_assist1(treetop, 2) == -1)
			return (-1);
		if (treetop->left && treetop->left->type == TYPE_PIPE)
			treetop = treetop->left;
		else
			break ;
	}
	if (temp->type == TYPE_PIPE && treetop->left \
			&& (treetop->left->type != TYPE_COMMAND \
			&& treetop->left->type != SINGLE_IN \
			&& treetop->left->type != SINGLE_OUT \
			&& treetop->left->type != DOUBLE_IN \
			&& treetop->left->type != DOUBLE_OUT))
		return (-1);
	return (0);
}

//runs the tree to setup check_valid_redirects2
int	check_valid_redirects(t_tree *treetop)
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
int	check_valid_redirects_2(t_tree *treetop)
{
	while (treetop && treetop->left)
	{
		if (treetop->left->type == SINGLE_IN
			|| treetop->left->type == SINGLE_OUT
			|| treetop->left->type == DOUBLE_IN
			|| treetop->left->type == DOUBLE_OUT)
		{
			if (!treetop->left->str && !treetop->left->left)
				return (-1);
		}
		if (treetop->left)
			treetop = treetop->left;
	}
	return (0);
}

int	syntax_checker_assist1(t_tree *treetop, int type)
{
	if (type == 1)
	{
		if ((treetop->type != TYPE_COMMAND \
			&& (treetop->type != SINGLE_IN && treetop->type != SINGLE_OUT \
			&& treetop->type != DOUBLE_IN && treetop->type != DOUBLE_OUT)) \
			|| (((treetop->type == SINGLE_IN || treetop->type == SINGLE_OUT \
			|| treetop->type == DOUBLE_IN || treetop->type == DOUBLE_OUT) \
			&& treetop->str == NULL)))
			return (-1);
	}
	if (type == 2)
	{
		if (!treetop->right || (treetop->right \
			&& (treetop->right->type != TYPE_COMMAND \
			&& treetop->right->type != SINGLE_IN \
			&& treetop->right->type != SINGLE_OUT \
			&& treetop->right->type != DOUBLE_IN \
			&& treetop->right->type != DOUBLE_OUT)))
			return (-1);
	}
	return (0);
}
