/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:06:10 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/17 16:01:31 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_env_line(char **envp, char *line_to_search)
{
	int	n;

	n = 0;
	while (envp && envp[n])
	{
		if (ft_strcmp(envp[n], line_to_search) == 0)
			break ;
		n++;
	}
	return (n);
}

int	search_part_line(char **envp, char *line_to_search, size_t len)
{
	int	n;

	n = 0;
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], line_to_search, len) == 0)
			break ;
		n++;
	}
	return (n);
}

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

void	remove_env_line(char **envp, int index)
{
	char	**tmp_env;
	int		len;
	int		n;

	n = 0;
	len = 0;
	while (envp && envp[len])
		len++;
	tmp_env = malloc(sizeof(char *) * len);
	if (!tmp_env)
		return ;
	len = 0;
	while (envp && envp[len])
	{
		if (n == index && envp[len + 1])
			len++;
		tmp_env[n] = ft_strdup(envp[len]);
		if (!tmp_env[n])
			return ;
		n++;
		len++;
	}
	tmp_env[n] = NULL;
	free(envp);
	envp = tmp_env;
}

char	*return_env_part_line(char **envp, int index)
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
	line = ft_substr(envp[n], ft_strlen2(envp[n], '=') + 1, ft_strlen(envp[n]) - ft_strlen2(envp[n], '='));
	return (line);
}

int		ft_strlen2(char *str, int sep)
{
	int	n;

	n = 0;
	while (str && str[n])
	{
		if (str[n] == sep)
			break ;
		n++;
	}
	return (n);
}

char	**add_env_line(char **envp, char *info_to_add)
{
	char	**tmp_env;
	int		len;
	int		n;

	n = 0;
	len = 0;
	while (envp && envp[len])
		len++;
	tmp_env = malloc(sizeof(char *) * len + 2);
	if (!tmp_env)
		return (NULL);
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], info_to_add, ft_strlen2(envp[n], '=')) != 0)
		{
			tmp_env[n] = ft_strdup(envp[n]);
			if (!tmp_env[n])
				return (NULL);
		}
		n++;
	}
	tmp_env[n] = ft_strdup(info_to_add);
	if (!tmp_env[n])
		return (NULL);
	tmp_env[n + 1] = NULL;
	return (tmp_env);
}

char	**replace_env_line(char **envp, char *info_to_add)
{
	char	**tmp_env;
	int		len;
	int		n;

	n = 0;
	len = 0;
	while (envp && envp[len])
		len++;
	tmp_env = malloc(sizeof(char *) * len + 1);
	if (!tmp_env)
		return (NULL);
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], info_to_add, ft_strlen2(envp[n], '=')) == 0)
			tmp_env[n] = ft_strdup(info_to_add);
		else
			tmp_env[n] = ft_strdup(envp[n]);
		n++;
	}
	tmp_env[n] = NULL;
	return (tmp_env);
}

char	**copy_env(char **envp)
{
	char	**new_env;
	int		len;
	
	len = 0;
	while (envp && envp[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 1));
	len = 0;
	while (envp && envp[len])
	{
		new_env[len] = ft_strdup(envp[len]);
		len++;
	}
	new_env[len] = NULL;
	return (new_env);
}
