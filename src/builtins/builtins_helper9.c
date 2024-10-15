/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:42:24 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/15 17:29:25 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ch_signal(int signal)
{
	t_global	info;

	info = global_info(NULL, NULL);
	info.envr->status = signal;
}

t_global	global_info(t_tree *tree, t_environment *envr)
{
	static t_global	info;

	if (tree)
		info.tree = tree;
	if (envr)
		info.envr = envr;
	return (info);
}
