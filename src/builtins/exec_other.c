/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:51:38 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/23 13:01:23 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_other(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	*path;
	pid_t	id;

	path = path_creator(cmd, envr);
	if (!path)
	{
		printf("%s : No such file or directory\n", cmd->str);
		clean_all_fds(envr->fds);
		//envr->status = 127;
		return ;
	}
	signal_decider(IGNORE);
	id = fork();
	if (id == 0)
		executer(cmd, tree, envr, path);
	else
	{
		waitpid(id, &envr->status, 0);
		clean_all_fds(envr->fds);
		envr->status = envr->status / 256;
		free(path);
	}
}

void	executer(t_tree *cmd, t_tree *tree, t_environment *envr, char *path)
{
	char	**av;
	int		*fd;

	av = build_av(tree, cmd);
	fd = ft_calloc(sizeof(int), 2);
	set_fds(cmd, av, path, fd);
	free(fd);
	clean_all_fds(envr->fds);
	signal_decider(CHILD);
	if (access(path, X_OK) == 0)
		if (execve(path, av, envr->env) == -1)
			perror("");
	free(path);
	clean_all_fds(envr->fds);
	free_env(av);
	exec_exit(1, 0, 1);
}

char	*path_creator(t_tree *cmd, t_environment *envr)
{
	char	**paths;
	char	*path;
	int		i;

	paths = NULL;
	if (ft_strncmp("./", cmd->str, 2) == 0)
		path = ft_substr(cmd->str, 2, ft_strlen(cmd->str) - 2);
	else if (ft_strncmp("/", cmd->str, 1) == 0)
		path = ft_strdup(cmd->str);
	else
	{
		i = search_part_line(envr->env, "PATH=", 5);
		if (i >= 0 && envr->env && envr->env[i])
		{
			paths = ft_split(envr->env[i], ':');
			if (!paths || !paths[0])
				return (NULL);
			paths[0] = paths[0] + 5;
		}
		path = check_path(paths, cmd->str);
	}
	if (path_creator_checker(envr, path) == 0)
		return (path);
	return (NULL);
}

char	*check_path(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!paths)
		return (NULL);
	if (cmd[0] == '\0')
		return (free_paths(paths), NULL);
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (free_paths(paths), path);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		if (i == 0)
			free(paths[i] - 5);
		else
			free(paths[i]);
		i++;
	}
	if (paths)
		free(paths);
}
