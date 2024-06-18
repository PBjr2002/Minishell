/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/18 17:01:15 by pauberna         ###   ########.fr       */
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

void	exec_unset(char **av, t_parser *info)
{
	char	**tmp_env;
	
	tmp_env = remove_env_line(info->env,
				search_part_line(info->env, av[1], ft_strlen(av[1])));
	free(info->env);
	info->env = tmp_env;
	free(info->export_env);
	info->export_env = copy_env(info->env, 0);
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
	char	**tmp;
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
	{
		execve(path, av, info->env);
		tmp = copy_env(info->env, 1);
		free(info->env);
		info->env = tmp;
	}
	else
	{
		wait(NULL);
		//free(path);
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
		free(tmp);
		if (!path)
			return (NULL);
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
