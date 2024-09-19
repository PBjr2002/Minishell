/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:06:39 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/19 16:56:44 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//just a simple function, to save space
void	tree_cleanup_function(t_tree *treetop)
{
	t_tree *temp;

	temp = treetop;
	if (treetop->type == TYPE_PIPE)
		check_valid_pipes(treetop);
}

//checks to see if pipes have commands attached to them, to avoid segfaults
void check_valid_pipes(t_tree *treetop)
{
	t_tree *temp;

	temp = treetop;
	while (treetop->type == TYPE_PIPE)
	{
		if (treetop->right->type != TYPE_COMMAND)
			SYNTAX_ERROR;
	}
}