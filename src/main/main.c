/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:56:06 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/23 14:22:54 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_environment	*info;
	t_lexer			*lexer;

	(void) av;
	lexer = NULL;
	if (ac != 1)
		return (ft_putendl_fd("Wrong number of arguments", 1), 1);
	info = calloc(sizeof(t_environment), 1);
	inicial_env(info, envp);
	prompt(info, lexer);
	return (0);
}

void	inicial_env(t_environment *info, char **envp)
{
	char	*pwd;
	char	*joined;

	joined = NULL;
	if (!envp[0])
	{
		add_info_to_env(info, NULL, "SHLVL=1");
		add_info_to_env(info, info->env, "PATH=/bin");
		pwd = getcwd(NULL, 0);
		joined = ft_strjoin("PWD=", pwd);
		free(pwd);
		add_info_to_env(info, info->env, joined);
		free(joined);
		add_info_to_env(info, info->env, "OLDPWD=");
		info->path_flag = 1;
	}
	else if (search_part_line(envp, "SHLVL", ft_strlen("SHLVL")) == -1)
		add_info_to_env(info, envp, "SHLVL=1");
	else
	{
		info->env = copy_env(envp, 1);
		info->export_env = copy_env(info->env, 0);
	}
	info->fds = 3;
}

void	add_info_to_env(t_environment *info, char **envp, char *str)
{
	char	**env;

	env = add_env_line(envp, str);
	free(info->env);
	free(info->export_env);
	info->env = copy_env(env, 0);
	info->export_env = copy_env(env, 0);
	free_env(env);
}
