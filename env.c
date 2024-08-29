/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/29 15:08:19 by pauberna         ###   ########.fr       */
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
	int		i;
	char	**tmp_export;
	char	**tmp_env;
	
	i = 1;
	while (av && av[i])
	{
		tmp_env = remove_env_line(info->env,
					search_part_line(info->env, av[i], ft_strlen(av[i])));
		tmp_export = remove_env_line(info->export_env,
					search_part_line(info->export_env, av[i], ft_strlen(av[i])));
		if (tmp_export)
		{
			free_env(info->export_env);
			info->export_env = tmp_export;
		}
		if (tmp_env)
		{
			free_env(info->env);
			info->env = tmp_env;
		}
		i++;
	}
}

void	exec_other(int fd, char **av, t_parser *info)
{
	char	*path;
	pid_t	id;

	
	path = path_creator(av, info);
	if (!path)
	{
		ft_putstr_fd(av[0], fd);
		ft_putstr_fd(": No such file or directory\n", fd);
		return ;
	}
	signal_decider(IGNORE);
	id = fork();
	if (id == 0)
	{
		signal_decider(CHILD);
		if (execve(path, av, info->env) == -1)
			perror("");
		exec_exit(0, av, info);
	}
	else
	{
		waitpid(id, NULL, 0);
		free(path);
	}
}

char	*path_creator(char **av, t_parser *info)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (ft_strncmp("./", av[0], 2) == 0)
		path = ft_substr(av[0], 2, ft_strlen(av[0]) - 2);
	else
	{
		i = search_part_line(info->env, "PATH=", 5);
		if (info->env[i])
		{
			paths = ft_split(info->env[i], ':');
			if (!paths || !paths[0])
				return (NULL);
			paths[0] = paths[0] + 5;
		}
		else
			paths = NULL;
		path = check_path(paths, av);
		
	}
	return (path);
}

char	*check_path(char **paths, char **av)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!paths)
		return (NULL);
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
		path = NULL;
		i++;
	}
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	return (free(paths), path);
}
