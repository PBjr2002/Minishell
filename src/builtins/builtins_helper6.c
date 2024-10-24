/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:04:15 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/21 15:32:09 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**env_to_print(char **envp, int mode)
{
	char	**tmp_env;
	int		n;

	n = 0;
	while (envp[n])
		n++;
	if (mode == 0)
		tmp_env = copy_env(envp, 0);
	else
	{
		if (search_part_line(envp, "PATH=", 5) == -1)
			tmp_env = copy_env(envp, 0);
		else
			tmp_env = remove_env_line(envp, search_part_line(envp, "PATH=", 5));
	}
	if (!tmp_env)
		return (NULL);
	return (sort_env(tmp_env, n - 1), tmp_env);
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
	int	n;
	int	i;

	n = 0;
	while (sorted[n])
	{
		i = 0;
		if ((sorted[n][i] >= 'A' && sorted[n][i] <= 'Z') ||
			(sorted[n][i] >= 'a' && sorted[n][i] <= 'z') || sorted[n][i] == '_')
		{
			ft_putstr_fd("declare -x ", fd);
			if (check_line(sorted[n]) == 0)
				ft_putendl_fd(sorted[n], fd);
			else if (check_line(sorted[n]) == 1)
				print_export_helper(sorted, fd, n, i);
			else if (check_line(sorted[n]) == 2)
				print_export_helper2(sorted, fd, n, i);
		}
		n++;
	}
}

void	print_export_helper(char **sorted, int fd, int n, int i)
{
	int	quotes;

	quotes = 0;
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

void	print_export_helper2(char **sorted, int fd, int n, int i)
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
