/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:55:40 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/12 15:53:24 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(int fd, char **av, char **envp)
{
	int		n;
	char	*cwd;
	char	*tmp;
	char	*new_cwd;
	char	*env_pwd;
	char	*old_pwd = NULL;
	char	**new_envp;
	char	**final_envp;

	//getcwd, dar strjoin disso com o input do user
	//com o chdir tentar alterar o diretorio atual, se der perfeito se nao dar uma mensagem de erro
	cwd = getcwd(NULL, 0);
	n = 0;
	if (!av[1])
	{
		tmp = return_env_line(envp, search_part_line(envp, "HOME=", 5));
		new_cwd = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
		free(tmp);
		old_pwd = getcwd(NULL, 0);
		chdir(new_cwd);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		tmp = return_env_line(envp, search_part_line(envp, "OLDPWD=", 7));
		new_cwd = ft_substr(tmp, 7, ft_strlen(tmp) - 7);
		ft_putendl_fd(new_cwd, fd);
		old_pwd = getcwd(NULL, 0);
		chdir(new_cwd);
	}
	else
	{
		tmp = ft_strjoin(cwd, "/");
		new_cwd = ft_strjoin(tmp, av[1]);
		free(tmp);
		old_pwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
		if (chdir(new_cwd) == -1)
		{
			ft_putstr_fd("minishell: cd: ", fd);
			ft_putstr_fd(av[1], fd);
			ft_putstr_fd(": ", fd);
			perror("");
			return ;
		}	
	}
	free(cwd);
	//printf("%s\n", getcwd(NULL, 0));
	cwd = getcwd(NULL, 0);
	env_pwd = ft_strjoin("PWD=", cwd);
	new_envp = add_env_line(envp, env_pwd);
	final_envp = add_env_line(new_envp, old_pwd);
	envp = final_envp;
	//alterar o cwd no env para poder ser possivel executar pwd
	//free(old_pwd);
	//old_pwd = ft_strdup(env_pwd);
	//free(env_pwd);
	//env_pwd = getcwd(NULL, sizeof(NULL));
	//adicionar o novo path para o env
}
