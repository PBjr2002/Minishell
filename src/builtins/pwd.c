/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:20:09 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/17 17:50:47 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_pwd(t_tree *cmd)
{
	char	*pwd;

	signal_decider(PIPE_CLOSED);
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	return (0);
}
