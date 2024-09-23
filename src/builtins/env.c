/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/23 16:38:34 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_env(t_tree *cmd, t_environment *envr)
{
	int		n;

	n = 0;
	while (envr->env[n])
	{
		ft_putendl_fd(envr->env[n], cmd->fd_out);
		n++;
	}
	return (0);
}

int	exec_unset(t_tree *tree, t_environment *envr)
{
	char	**tmp_export;
	char	**tmp_env;

	while (tree && tree->str)
	{
		tmp_env = remove_env_line(envr->env,
				search_part_line(envr->env, tree->str, ft_strlen(tree->str)));
		tmp_export = remove_env_line(envr->export_env,
				search_part_line(envr->export_env, tree->str,
					ft_strlen(tree->str)));
		if (tmp_export)
		{
			free_env(envr->export_env);
			envr->export_env = tmp_export;
		}
		if (tmp_env)
		{
			free_env(envr->env);
			envr->env = tmp_env;
		}
		tree = tree->right;
	}
	return (0);
}
