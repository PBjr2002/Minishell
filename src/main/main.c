/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:56:06 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/18 14:23:57 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_environment	*info;
	t_lexer			*lexer;
	char			**env;

	(void) av;
	lexer = NULL;
	if (ac != 1)
		return (ft_putendl_fd("Wrong number of arguments", 1), 1);
	info = calloc(sizeof(t_environment), 1);
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
	info->fds = 3;
	prompt(info, lexer);
	return (0);
}
