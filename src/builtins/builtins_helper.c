/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:06:10 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/23 13:26:25 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**copy_env(char **envp, int mode)
{
	char	**new_env;
	char	*lvl;
	int		len;

	len = 0;
	lvl = return_part_line(envp, search_part_line(envp, "SHLVL=", 6), 0);
	while (envp && envp[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	if (copy_env_helper(new_env, envp, lvl, mode) == 1)
		return (free(lvl), free_env(new_env), NULL);
	free(lvl);
	return (new_env);
}

int	copy_env_helper(char **new_env, char **envp, char *lvl, int mode)
{
	char	*new_lvl;
	int		l;
	int		len;

	len = 0;
	while (envp && envp[len])
	{
		if (mode == 1 && !lvl)
			new_env[len] = ft_strdup("SHLVL=1");
		else if (mode == 1 && len == search_part_line(envp, "SHLVL=", 6))
		{
			l = ft_atoi(lvl);
			l++;
			new_lvl = ft_itoa(l);
			new_env[len] = ft_strjoin("SHLVL=", new_lvl);
			free(new_lvl);
		}
		else
			new_env[len] = ft_strdup(envp[len]);
		if (!new_env[len])
			return (1);
		len++;
	}
	new_env[len] = NULL;
	return (0);
}

char	**remove_env_line(char **envp, int index)
{
	char	**tmp_env;
	int		len;

	len = 0;
	if (index < 0)
		return (NULL);
	while (envp && envp[len])
		len++;
	tmp_env = malloc(sizeof(char *) * len);
	if (!tmp_env)
		return (NULL);
	if (remove_env_helper(envp, tmp_env, index) == 1)
		return (free_env(tmp_env), NULL);
	return (tmp_env);
}

int	remove_env_helper(char **envp, char **tmp_env, int index)
{
	int	n;
	int	len;

	len = 0;
	n = 0;
	while (envp && envp[len])
	{
		if (n == index)
			len++;
		if (envp[len])
		{
			tmp_env[n] = ft_strdup(envp[len]);
			if (!tmp_env[n])
				return (1);
		}
		else
			break ;
		n++;
		len++;
	}
	tmp_env[n] = NULL;
	return (0);
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
	tmp_env = malloc(sizeof(char *) * (len + 2));
	if (!tmp_env)
		return (NULL);
	while (envp && envp[n])
	{
		tmp_env[n] = ft_strdup(envp[n]);
		if (!tmp_env[n])
			return (NULL);
		n++;
	}
	tmp_env[n] = ft_strdup(info_to_add);
	if (!tmp_env[n])
		return (NULL);
	tmp_env[n + 1] = NULL;
	return (tmp_env);
}
