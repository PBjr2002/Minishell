/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/16 16:02:08 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decider(char *cmd)
{
	int		i;

	i = 0;
	while (info->cmds[i])
	{
	}
	
	if (ft_strcmp(cmd, "echo") == 0)
		exec_echo(fd, av, info);
	else if (ft_strcmp(cmd, "cd") == 0)
		exec_cd(fd, av, info);
	else if (ft_strcmp(cmd, "pwd") == 0)
		exec_pwd(fd);
	else if (ft_strcmp(cmd, "export") == 0)
		exec_export(fd, av, info);
	else if (ft_strcmp(cmd, "env") == 0)
		exec_env(fd, info);
	else if (ft_strcmp(cmd, "exit") == 0)
		prepare_exit(av, info);
	else if (ft_strcmp(cmd, "unset") == 0)
		exec_unset(av, info);
	else
		exec_other(fd, av, info);
}

void	search_tree(t_tree *tree)
{
	while (tree)
	{
		while (tree && tree->type != 8)
			tree = tree->left;
		if (tree)
		{
			if (tree->left)
			{
				while (tree)
					tree = tree->left;
				redirect_solver;
			}
			
			decider(tree->str);
			tree->solved = true;
		}
	}
	
	
}
