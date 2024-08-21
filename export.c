/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:26:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/13 13:27:15 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(int fd, char **av, t_parser *info)
{
	int		n;
	int		i;
	char	**sorted;
	char	**new_export;
	char	**new_env;

	if (!av[1])
	{
		n = 0;
		sorted = env_to_print(info->export_env);
		if (!sorted)
			return ;
		print_export(fd, sorted);
		free_env(sorted);
	}
	else
	{
		i = 1;
		while (av[i])
		{
			n = 0;
			while (info->export_env[n])
			{
				if (ft_strncmp(av[i], info->export_env[n], ft_strlen2(av[i], '=')) == 0 &&
					ft_strlen2(av[i], '=') == ft_strlen2(info->export_env[n], '='))
					break ;
				n++;
			}
			if (info->export_env[n])
			{
				new_export = replace_line(info->export_env, av[i]);
				free_env(info->export_env);
				info->export_env = new_export;
			}
			else
			{
				new_export = add_env_line(info->export_env, av[i]);
				free_env(info->export_env);
				info->export_env = new_export;
				if (check_line(av[i]) != 0)
				{
					new_env = add_env_line(info->env, av[i]);
					free_env(info->env);
					info->env = new_env;
				}
			}
			i++;
		}
	}
}

char	**env_to_print(char **envp)
{
	char	**tmp_env;
	int		n;

	n = 0;
	while (envp[n])
		n++;
	tmp_env = malloc(sizeof(char *) * (n + 1));
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
			if (check_line(sorted[n]) == 0)
				ft_putendl_fd(sorted[n], fd);
			else if (check_line(sorted[n]) == 1)
			{
				while (sorted[n][i])
				{
					if (sorted[n][i] != '"')
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
			}
			else if (check_line(sorted[n]) == 2)
			{
				while (sorted[n][i])
				{
					ft_putchar_fd(sorted[n][i], fd);
					if (sorted[n][i] == '=')
					{
						ft_putendl_fd("\"\"", fd);
						break ;
					}
					i++;
				}
			}
		}
		n++;
	}
}

int		check_line(char *line)
{
	int	checker;
	int	n;

	checker = 0;
	n = 0;
	if (!line)
		return (-1);
	while (line && line[n])
	{
		if (line[n] == '=')
		{
			if (line[n + 1])
				checker = 1;
			else
				checker = 2;
			break ;
		}
		n++;
	}
	return (checker);
}
