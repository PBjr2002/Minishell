/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:56:06 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/29 13:13:30 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_parser	*info;
	char		**env;

	(void) av;
	if (ac != 1)
		return (1);
	info = malloc(sizeof(t_parser));
	if (search_part_line(envp, "SHLVL", ft_strlen("SHLVL")) == -1)
	{
		env = add_env_line(envp, "SHLVL=1");
		free(info->env);
		free(info->export_env);
		info->env = copy_env(env, 0);
		info->export_env = copy_env(env, 0);
	}
	else
	{
		info->env = copy_env(envp, 1);
		info->export_env = copy_env(info->env, 0);
	}
	prompt(info);
	return (0);
}
