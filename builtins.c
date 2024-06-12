/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/12 16:09:56 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decider(int ac, char **av, char **envp)
{
	int	fd;

	fd = 1;
	(void) ac;
	if (ft_strcmp(av[0], "echo") == 0)
		exec_echo(fd, av);
	else if (ft_strcmp(av[0], "cd") == 0)
		exec_cd(fd, av, envp);
	else if (ft_strcmp(av[0], "pwd") == 0)
		exec_pwd(fd, envp);
	else if (ft_strcmp(av[0], "export") == 0)
		exec_export(fd, av, envp);
	else if (ft_strcmp(av[0], "env") == 0)
		exec_env(fd, envp);
	else if (ft_strcmp(av[0], "exit") == 0)
		exec_exit(fd, envp);
	/* else if (ft_strcmp(str, "unset") == 0)
		exec_unset(str, envp); */
}
