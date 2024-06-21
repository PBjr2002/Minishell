/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:55:40 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/19 15:47:57 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(int fd, char **av, t_parser *info)
{
	char	*cwd;
	char	*tmp;
	char	*new_cwd;
	char	*env_pwd;
	char	*old_pwd;
	char	**new_envp;

	cwd = return_part_line(info->env, search_part_line(info->env, "PWD=", 4), 0);
	if (!av[1])
	{
		new_cwd = return_part_line(info->env, search_part_line(info->env, "HOME=", 5), 0);
		tmp = return_part_line(info->env, search_part_line(info->env, "PWD=", 4), 0);
		old_pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		chdir(new_cwd);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		new_cwd = return_part_line(info->env, search_part_line(info->env, "OLDPWD=", 7), 0);
		ft_putendl_fd(new_cwd, fd);
		tmp = return_part_line(info->env, search_part_line(info->env, "PWD=", 4), 0);
		old_pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		chdir(new_cwd);
	}
	else
	{
		if (ft_strcmp(av[1], "..") == 0)
		{
			old_pwd = ft_strjoin("OLDPWD=", cwd);
			if (chdir(av[1]) == -1)
			{
				ft_putstr_fd("minishell: cd: ", fd);
				ft_putstr_fd(av[1], fd);
				ft_putstr_fd(": ", fd);
				perror("");
				return ;
			}
			new_cwd = getcwd(NULL, 0);
		}
		else
		{
			if (ft_strlen(ft_strrchr(cwd, '/')) != 1)
			{
				tmp = ft_strjoin(cwd, "/");
				new_cwd = ft_strjoin(tmp, av[1]);
				free(tmp);
			}
			else
				new_cwd = ft_strjoin(cwd, av[1]);
			old_pwd = ft_strjoin("OLDPWD=", cwd);
			if (chdir(av[1]) == -1)
			{
				ft_putstr_fd("minishell: cd: ", fd);
				ft_putstr_fd(av[1], fd);
				ft_putstr_fd(": ", fd);
				perror("");
				return ;
			}
		}	
	}
	free(cwd);
	env_pwd = ft_strjoin("PWD=", new_cwd);
	new_envp = replace_line(info->env, env_pwd);
	free(info->env);
	info->env = replace_line(new_envp, old_pwd);
	free(new_envp);
}
