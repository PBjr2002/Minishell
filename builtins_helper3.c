/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:22:12 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/30 16:24:40 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_env_line(char **envp, int index)
{
	char	*line;
	int		n;

	n = 0;
	while (envp && envp[n])
	{
		if (n == index)
			break ;
		n++;
	}
	line = ft_strdup(envp[n]);
	if (!line)
		return (NULL);
	return (line);
}

char	*return_part_line(char **envp, int index, int mode)
{
	char	*line;
	int		n;

	line = NULL;
	n = 0;
	if (index == -1)
		return (NULL);
	while (envp && envp[n])
	{
		if (n == index)
			break ;
		n++;
	}
	if (envp[n])
	{
		if (mode == 0)
			line = ft_substr(envp[n], ft_strlen2(envp[n], '=') + 1, ft_strlen(envp[n]) - ft_strlen2(envp[n], '='));
		else if (mode == 1)
			line = ft_substr(envp[n], 0, ft_strlen2(envp[n], '='));
	}
	return (line);
}

void	free_env(char **env)
{
	int	n;

	n = 0;
	while (env && env[n])
	{
		free(env[n]);
		n++;
	}
	free(env);
}

char	*ft_getpid(void)
{
	char	**split;
	char	*pid;
	int		fd;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (NULL);
	pid = get_next_line(fd);
	close(fd);
	if (!pid)
		return (NULL);
	split = ft_split(pid, ' ');
	if (!split)
		return (NULL);
	free(pid);
	pid = ft_strdup(split[0]);
	free_env(split);
	return (pid);
}
