/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:26:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/18 16:39:30 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(int fd, char **av, t_parser *info)
{
	char	**sorted;
	char	**new_env;

	if (!av[1])
	{
		sorted = env_to_print(info->export_env);
		if (!sorted)
			return ;
		print_export(fd, sorted);
		free(sorted);
	}
	//corrigir o export=algo
	else
	{
		new_env = add_env_line(info->export_env, av[1]);
		free(info->export_env);
		info->export_env = new_env;
		//sorted = env_to_print(new_env);
		//if (!sorted)
		//	return ;
		//print_export(fd, envp);
		//free(sorted);
	}
}

char	**env_to_print(char **envp)
{
	char	**tmp_env;
	int		n;

	n = 0;
	while (envp[n])
		n++;
	tmp_env = malloc(sizeof(char *) * n + 1);
	if (!tmp_env)
		return (NULL);
	n = 0;
	while (envp[n])
	{
		tmp_env[n] = ft_strdup(envp[n]);
		n++;
	}
	tmp_env[n] = NULL;
	sort_env(tmp_env, n - 1);
	return (tmp_env);
}

void	sort_env(char **new_env, int limit)
{
	char	*tmp;
	int		n;

	n = 0;
	while (n < limit)
	{
		if (ft_strcmp(new_env[n], new_env[n + 1]) > 0)
		{
			tmp = ft_strdup(new_env[n]);
			free(new_env[n]);
			new_env[n] = ft_strdup(new_env[n + 1]);
			free(new_env[n + 1]);
			new_env[n + 1] = ft_strdup(tmp);
			free(tmp);
			n = 0;
		}
		else
			n++;
	}
}

void	print_export(int fd, char **sorted)
{
	int	quotes;
	int	n;
	int	i;

	n = 0;
	while (sorted[n])
	{
		i = 0;
		quotes = 0;
		if ((sorted[n][i] >= 'A' && sorted[n][i] <= 'Z') ||
			(sorted[n][i] >= 'a' && sorted[n][i] <= 'z'))
		{
			ft_putstr_fd("declare -x ", fd);
			while (sorted[n][i])
			{
				ft_putchar_fd(sorted[n][i], fd);
				if (sorted[n][i] == '=' && quotes == 0)
				{
					ft_putchar_fd('"', fd);
					quotes = 1;
				}
				i++;
			}
			ft_putchar_fd('"', fd);
			ft_putchar_fd('\n', fd);
			free(sorted[n]);
		}
		n++;
	}
	//free(sorted[n]);
}
