/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:22:12 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/13 13:24:06 by pauberna         ###   ########.fr       */
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
	while (envp && envp[n])
	{
		if (n == index)
			break ;
		n++;
	}
	if (mode == 0)
		line = ft_substr(envp[n], ft_strlen2(envp[n], '=') + 1, ft_strlen(envp[n]) - ft_strlen2(envp[n], '='));
	else if (mode == 1)
		line = ft_substr(envp[n], 0, ft_strlen2(envp[n], '='));
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
