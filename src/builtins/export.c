/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:26:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/11 12:46:14 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_export(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	**sorted;

	if (!tree)
	{
		sorted = env_to_print(envr->export_env);
		if (!sorted)
			return (1);
		print_export(cmd->fd_out, sorted);
		free_env(sorted);
	}
	else
		export_helper(tree, cmd, envr);
	return (0);
}

void	export_helper(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	n;

	while (tree)
	{
		n = 0;
		while (envr->export_env[n])
		{
			if (ft_strncmp(tree->str, envr->export_env[n],
					ft_strlen2(tree->str, '=')) == 0
				&& ft_strlen2(tree->str, '=')
				== ft_strlen2(envr->export_env[n], '='))
				break ;
			n++;
		}
		if (envr->export_env[n])
			export_helper2(tree, envr);
		else
			export_helper3(cmd, tree, envr);
		tree = tree->right;
	}
}

void	export_helper2(t_tree *tree, t_environment *envr)
{
	char	**new_env;
	char	**new_export;

	new_export = replace_line(envr->export_env, tree->str);
	free_env(envr->export_env);
	envr->export_env = new_export;
	if (search_part_line(envr->export_env, tree->str,
			ft_strlen2(tree->str, '=')) != -1)
	{
		if (check_line(tree->str) == 0)
		{
			new_env = remove_env_line(envr->export_env,
							search_env_line(envr->export_env, tree->str));
			free(envr->env);
			envr->env = new_env;
		}
		else
		{
			new_env = replace_line(envr->export_env, tree->str);
			free_env(envr->env);
			envr->env = new_env;
		}
	}
}

void	export_helper3(t_tree *cmd, t_tree *tree, t_environment *envr)
{
	char	**new_env;
	char	**new_export;

	if (check_argument(tree->str) == 0)
	{
		new_export = add_env_line(envr->export_env, tree->str);
		free_env(envr->export_env);
		envr->export_env = new_export;
		if (check_line(tree->str) != 0)
		{
			new_env = add_env_line(envr->env, tree->str);
			free_env(envr->env);
			envr->env = new_env;
		}
	}
	else
	{
		ft_putstr_fd("minishell: export: ", cmd->fd_out);
		ft_putstr_fd(tree->str, cmd->fd_out);
		ft_putendl_fd(": not a valid identifier", cmd->fd_out);
	}
}

int	check_argument(char *str)
{
	int	n;

	n = 0;
	while (str && str[n])
	{
		if (str[n] == '=')
			break ;
		else if ((ft_isalnum(str[n] == 0) && str[n] != '_')
			|| (ft_isdigit(str[n]) == 1 && n == 0))
			return (-1);
		n++;
	}
	if (n == 0)
		return (-1);
	return (0);
}
