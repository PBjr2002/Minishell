/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:06:39 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/19 17:53:56 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//just a simple function, to save space, if syntax error, status = 2
void	tree_cleanup_function(t_tree *treetop, t_environment *info)
{
	t_tree *temp;

	temp = treetop;
	if (check_valid_pipes(treetop) == -1)
		info->status = 2;
}

//checks to see if pipes have commands attached to them, to avoid segfaults
//without my intention, it also checks if commands are present if a pipeless input is sent...
int check_valid_pipes(t_tree *treetop)
{
	t_tree *temp;

	temp = treetop;
	if (treetop->type != TYPE_PIPE)
	{
		if (treetop->type != TYPE_COMMAND)
			return (-1);
	}
	while (treetop->type == TYPE_PIPE)
	{
		ft_printf("Current str %s Current type %d Current pipeline %d\n", treetop->str, treetop->type, treetop->pipeline);
		if (treetop->left)
			ft_printf("Left str %s Left type %d Current pipeline %d\n", treetop->left->str, treetop->left->type, treetop->pipeline);
		if (treetop->right)
			ft_printf("Right str %s Right type %d Current pipeline %d\n", treetop->right->str, treetop->right->type, treetop->pipeline);
		if (!treetop->right || treetop->right->type != TYPE_COMMAND)
			return (-1);
		if (treetop->left && treetop->left->type == TYPE_PIPE)
			treetop = treetop->left;
		else
			break;
	}
	if (treetop->left && treetop->left->type != TYPE_COMMAND)
		return (-1);
	return (0);
}
