/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/17 16:24:13 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(int fd, t_parser *info)
{
	int		n;

	n = 0;
	while (info->env[n])
	{
		ft_putendl_fd(info->env[n], fd);
		n++;
	}
}

void	exec_exit(int signal, char **av)
{
	(void) signal;
	(void) av;
	exit(EXIT_SUCCESS);
}

void	exec_other(int fd, char **av, t_parser *info)
{
	char	**paths;
	char	*path;
	int		i;
	int		id;

	i = 0;
	(void) fd;
	while (info->env[i])
	{
		if (ft_strncmp(info->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(info->env[i], ':');
	if (!paths)
		return ;
	paths[0] = paths[0] + 5;
	path = check_path(paths, av);
	if (!path)
		return ;
	id = fork();
	if (id == 0)
		execve(path, av, info->env);
	else
	{
		wait(NULL);
		free(path);
	}
}

char	*check_path(char **paths, char **av)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, av[0]);
		if (!path)
			return (NULL);
		free(tmp);
		if (access(path, X_OK) == 0)
			break ;
		if (i == 0)
			free(paths[i] - 5);
		else
			free(paths[i]);
		free(path);
		i++;
	}
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	return (free(paths), path);
}
