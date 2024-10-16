/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:55:40 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/16 17:29:54 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cd(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	t_cd	*cd;

	cd = ft_calloc(sizeof(t_cd), 1);
	cd->cwd = return_part_line(envr->env,
			search_part_line(envr->env, "PWD=", 4), 0);
	if (!tree)
		cd_helper(envr, cd);
	else if (tree->null_char == true)
		return (0);
	else if (ft_strcmp(tree->str, "-") == 0)
		cd_helper2(cmd, envr, cd);
	else
	{
		if (ft_strcmp(tree->str, "..") == 0)
		{
			if (cd_helper3(tree, cmd, cd) == 1)
				return (1);
		}
		else
			if (cd_helper4(tree, cmd, cd) == 1)
				return (1);
	}
	cd_cleaner(envr, cd);
	return (0);
}
