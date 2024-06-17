/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:55:40 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/17 16:55:30 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(int fd, char **av, t_parser *info)
{
	char	*cwd;
	char	*tmp;
	char	*new_cwd;
	char	*env_pwd;
	char	*old_pwd = NULL;
	char	**new_envp;
	char	**final_envp;

	cwd = return_env_part_line(info->env, search_part_line(info->env, "PWD=", 4));
	if (!av[1])
	{
		new_cwd = return_env_part_line(info->env, search_part_line(info->env, "HOME=", 5));
		tmp = return_env_part_line(info->env, search_part_line(info->env, "PWD=", 4));
		old_pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		chdir(new_cwd);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		new_cwd = return_env_part_line(info->env, search_part_line(info->env, "OLDPWD=", 7));
		ft_putendl_fd(new_cwd, fd);
		tmp = return_env_part_line(info->env, search_part_line(info->env, "PWD=", 4));
		old_pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		chdir(new_cwd);
	}
	else
	{
		tmp = ft_strjoin(cwd, "/");
		new_cwd = ft_strjoin(tmp, av[1]);
		free(tmp);
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
	free(cwd);
	env_pwd = ft_strjoin("PWD=", new_cwd);
	ft_putendl_fd(env_pwd, fd);
	new_envp = replace_env_line(info->env, env_pwd);
	ft_putendl_fd(old_pwd, fd);
	final_envp = replace_env_line(new_envp, old_pwd);
	free(info->env);
	info->env = copy_env(final_envp);
}
