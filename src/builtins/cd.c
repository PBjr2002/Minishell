/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:55:40 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/19 11:28:36 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cd(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	*cwd;

	char	*tmp;
	char	*new_cwd;
	char	*env_pwd;
	char	*old_pwd;
	char	**new_envp;
	char	**new_export;

	cwd = return_part_line(envr->env, search_part_line(envr->env, "PWD=", 4), 0);
	if (!tree)
	{
		new_cwd = return_part_line(envr->env, search_part_line(envr->env, "HOME=", 5), 0);
		tmp = return_part_line(envr->env, search_part_line(envr->env, "PWD=", 4), 0);
		old_pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		chdir(new_cwd);
	}
	else if (ft_strcmp(tree->str, "-") == 0)
	{
		new_cwd = return_part_line(envr->env, search_part_line(envr->env, "OLDPWD=", 7), 0);
		ft_putendl_fd(new_cwd, cmd->fd_out);
		tmp = return_part_line(envr->env, search_part_line(envr->env, "PWD=", 4), 0);
		old_pwd = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		chdir(new_cwd);
	}
	else
	{
		
		if (ft_strcmp(tree->str, "..") == 0)
		{
			old_pwd = ft_strjoin("OLDPWD=", cwd);
			if (chdir(tree->str) == -1)
			{
				ft_putstr_fd("minishell: cd: ", cmd->fd_out);
				ft_putstr_fd(tree->str, cmd->fd_out);
				ft_putstr_fd(": ", cmd->fd_out);
				perror("");
				return (1);
			}
			new_cwd = getcwd(NULL, 0);
		}
		else
		{
			if (ft_strlen(ft_strrchr(cwd, '/')) != 1)
			{
				tmp = ft_strjoin(cwd, "/");
				new_cwd = ft_strjoin(tmp, tree->str);
				free(tmp);
			}
			else
				new_cwd = ft_strjoin(cwd, tree->str);
			old_pwd = ft_strjoin("OLDPWD=", cwd);
			if (chdir(tree->str) == -1)
			{
				free(cwd);
				free(new_cwd);
				free(old_pwd);
				ft_putstr_fd("minishell: cd: ", cmd->fd_out);
				ft_putstr_fd(tree->str, cmd->fd_out);
				ft_putstr_fd(": ", cmd->fd_out);
				perror("");
				return (1);
			}
		}	
	}
	free(cwd);
	env_pwd = ft_strjoin("PWD=", new_cwd);
	new_envp = replace_line(envr->env, env_pwd);
	free_env(envr->env);
	envr->env = replace_line(new_envp, old_pwd);
	free_env(new_envp);
	new_export = replace_line(envr->export_env, env_pwd);
	free_env(envr->export_env);
	envr->export_env = replace_line(new_export, old_pwd);
	free_env(new_export);
	free(new_cwd);
	free(env_pwd);
	free(old_pwd);
	return (0);
}
