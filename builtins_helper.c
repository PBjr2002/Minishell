/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:06:10 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/27 17:20:20 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp, int mode)
{
	char	**new_env;
	char	*lvl;
	char	*new_lvl;
	int		len;
	int		l;
	
	len = 0;
	lvl = return_part_line(envp, search_part_line(envp, "SHLVL=", 6), 0);
	while (envp && envp[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 1));
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
		len++;
	}
	new_env[len] = NULL;
	free(lvl);
	return (new_env);
}

char	**remove_env_line(char **envp, int index)
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
		return (NULL);
	len = 0;
	while (envp && envp[len])
	{
		if (n == index)
			len++;
		if (envp[len])
		{
			tmp_env[n] = ft_strdup(envp[len]);
			if (!tmp_env[n])
				return (NULL);
		}
		else
			break ;
		n++;
		len++;
	}
	tmp_env[n] = NULL;
	return (tmp_env);
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

char	**replace_line(char **envp, char *info_to_add)
{
	char	**tmp_env;
	int		len;
	int		n;

	n = 0;
	len = 0;
	while (envp && envp[len])
		len++;
	tmp_env = malloc(sizeof(char *) * (len + 1));
	if (!tmp_env)
		return (NULL);
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], info_to_add, ft_strlen2(envp[n], '=')) == 0 &&
			ft_strlen2(envp[n], '=') == ft_strlen2(info_to_add, '='))
			tmp_env[n] = ft_strdup(info_to_add);
		else
			tmp_env[n] = ft_strdup(envp[n]);
		if (!tmp_env[n])
			return (NULL);
		n++;
	}
	tmp_env[n] = NULL;
	return (tmp_env);
}

char	**replace_value(char **envp, int index, int value)
{
	char	**tmp_env;
	char	*nb;
	char	*tmp;
	int		n;

	n = 0;
	while (envp && envp[n])
		n++;
	tmp_env = malloc(sizeof(char *) * (n + 1));
	if (!tmp_env)
		return (NULL);
	nb = ft_itoa(value);
	if (!nb)
		return (NULL);
	n = 0;
	while (envp && envp[n])
	{
		if (n == index)
		{
			tmp = return_part_line(envp, search_env_line(envp, tmp_env[n]), 1);
			tmp_env[n] = ft_strjoin(tmp, nb);
			free(tmp);
		}
		else
			tmp_env[n] = ft_strdup(envp[n]);
		if (!tmp_env[n])
			return (NULL);
		n++;
	}
	tmp_env[n] = NULL;
	return (tmp_env);
}
