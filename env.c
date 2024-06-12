/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/11 17:33:48 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(int fd, char **envp)
{
	int		n;

	n = 0;
	while (envp[n])
	{
		ft_putendl_fd(envp[n], fd);
		n++;
	}
}

void	exec_exit(int signal, char **av)
{
	(void) signal;
	(void) av;
	exit(EXIT_SUCCESS);
}
