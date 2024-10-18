/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:55:06 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/18 16:09:20 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_helper(t_tree *cmd, t_environment *envr, t_cd *cd)
{
	if (search_part_line(envr->env, "HOME=", 5) == -1)
	{
		ft_putendl_fd("minishell: cd: HOME not set", cmd->fd_out);
		return ;
	}
	cd->new_cwd = return_part_line(envr->env,
			search_part_line(envr->env, "HOME=", 5), 0);
	cd->tmp = return_part_line(envr->env,
			search_part_line(envr->env, "PWD=", 4), 0);
	cd->old_pwd = ft_strjoin("OLDPWD=", cd->tmp);
	free(cd->tmp);
	chdir(cd->new_cwd);
}

void	cd_helper2(t_tree *cmd, t_environment *envr, t_cd *cd)
{
	cd->new_cwd = return_part_line(envr->env,
			search_part_line(envr->env, "OLDPWD=", 7), 0);
	ft_putendl_fd(cd->new_cwd, cmd->fd_out);
	cd->tmp = return_part_line(envr->env,
			search_part_line(envr->env, "PWD=", 4), 0);
	cd->old_pwd = ft_strjoin("OLDPWD=", cd->tmp);
	free(cd->tmp);
	chdir(cd->new_cwd);
}

int	cd_helper3(t_tree *tree, t_tree *cmd, t_cd *cd)
{
	cd->tmp = getcwd(NULL, 0);
	cd->old_pwd = ft_strjoin("OLDPWD=", cd->tmp);
	free(cd->tmp);
	if (chdir(tree->str) == -1)
	{
		ft_putstr_fd("minishell: cd: ", cmd->fd_out);
		ft_putstr_fd(tree->str, cmd->fd_out);
		ft_putstr_fd(": ", cmd->fd_out);
		perror("");
		return (1);
	}
	if (cd->cwd)
		cd->new_cwd = getcwd(NULL, 0);
	else
		cd->new_cwd = NULL;
	return (0);
}

int	cd_helper4(t_tree *tree, t_tree *cmd, t_cd *cd)
{
	if (ft_strlen(ft_strrchr(cd->cwd, '/')) != 1)
	{
		cd->tmp = ft_strjoin(cd->cwd, "/");
		cd->new_cwd = ft_strjoin(cd->tmp, tree->str);
		free(cd->tmp);
	}
	else
		cd->new_cwd = ft_strjoin(cd->cwd, tree->str);
	if (cd->cwd)
		cd->old_pwd = ft_strjoin("OLDPWD=", cd->cwd);
	else
	{
		cd->tmp = getcwd(NULL, 0);
		cd->old_pwd = ft_strjoin("OLDPWD=", cd->tmp);
		free(cd->tmp);
	}
	if (chdir(tree->str) == -1)
	{
		ft_putstr_fd("minishell: cd: ", cmd->fd_out);
		ft_putstr_fd(tree->str, cmd->fd_out);
		ft_putstr_fd(": ", cmd->fd_out);
		perror("");
		return (free(cd->new_cwd), free(cd->old_pwd), 1);
	}
	return (0);
}

void	cd_cleaner(t_environment *envr, t_cd *cd, int mode)
{
	if (mode == 0)
	{
		cd->env_pwd = ft_strjoin("PWD=", cd->new_cwd);
		cd->new_envp = replace_line(envr->env, cd->env_pwd);
		free_env(envr->env);
		envr->env = replace_line(cd->new_envp, cd->old_pwd);
		free_env(cd->new_envp);
		cd->new_export = replace_line(envr->export_env, cd->env_pwd);
		free_env(envr->export_env);
		envr->export_env = replace_line(cd->new_export, cd->old_pwd);
		free_env(cd->new_export);
		free(cd->new_cwd);
		free(cd->env_pwd);
		free(cd->old_pwd);
	}
	free(cd->cwd);
	free(cd);
}
