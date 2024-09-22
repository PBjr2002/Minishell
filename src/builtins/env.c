/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/22 18:53:17 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_env(t_tree *cmd, t_environment *envr)
{
	int		n;

	n = 0;
	while (envr->env[n])
	{
		ft_putendl_fd(envr->env[n], cmd->fd_out);
		n++;
	}
	return (0);
}

int	exec_unset(t_tree *tree, t_environment *envr)
{
	char	**tmp_export;
	char	**tmp_env;
	
	while (tree && tree->str)
	{
		tmp_env = remove_env_line(envr->env,
					search_part_line(envr->env, tree->str, ft_strlen(tree->str)));
		tmp_export = remove_env_line(envr->export_env,
					search_part_line(envr->export_env, tree->str, ft_strlen(tree->str)));
		if (tmp_export)
		{
			free_env(envr->export_env);
			envr->export_env = tmp_export;
		}
		if (tmp_env)
		{
			free_env(envr->env);
			envr->env = tmp_env;
		}
		tree = tree->right;
	}
	return (0);
}

void	exec_other(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	*path;
	char	**av;
	
	path = path_creator(cmd, envr);
	if (!path)
	{
		ft_putstr_fd(cmd->str, cmd->fd_out);
		ft_putstr_fd(": No such file or directory\n", cmd->fd_out);
		return ;
	}
	signal_decider(IGNORE);
	av = build_av(tree, cmd);
	envr->pid = fork();
	if (envr->pid == 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			printf("There was an error duplicating the FD\n");
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			printf("There was an error duplicating the FD\n");
		fd_closer(cmd, 0);
		signal_decider(CHILD);
		if (access(path, X_OK) == 0)
			if (execve(path, av, envr->env) == -1)
				perror("");
		free_env(av);
		exec_exit(0, tree, cmd, envr);
	}
	else
	{
		waitpid(envr->pid, &envr->status, 0);
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != STDOUT_FILENO
			&& cmd->fd_in != STDERR_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDIN_FILENO && cmd->fd_out != STDOUT_FILENO
			&& cmd->fd_out != STDERR_FILENO)
			close(cmd->fd_out);
		envr->status = envr->status / 256;
		free_env(av);
		free(path);
	}
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
	if (path)
		if (access(path, F_OK) == 0)
			if (access(path, X_OK) == 0)
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
		if (i == 0)
			free(paths[i] - 5);
		else
			free(paths[i]);
		i++;
	}
	return (free(paths), path);
}
