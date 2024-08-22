/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/09 16:54:16 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decider(int ac, char **av, t_parser *info)
{
	int	fd;

	fd = 1;
	(void) ac;
	if (ft_strcmp(av[0], "echo") == 0)
		exec_echo(fd, av);
	else if (ft_strcmp(av[0], "cd") == 0)
		exec_cd(fd, av, info);
	else if (ft_strcmp(av[0], "pwd") == 0)
		exec_pwd(fd);
	else if (ft_strcmp(av[0], "export") == 0)
		exec_export(fd, av, info);
	else if (ft_strcmp(av[0], "env") == 0)
		exec_env(fd, info);
	else if (ft_strcmp(av[0], "exit") == 0)
		exec_exit(fd, av, info);
	else if (ft_strcmp(av[0], "unset") == 0)
		exec_unset(av, info);
	else
		exec_other(fd, av, info);
}
