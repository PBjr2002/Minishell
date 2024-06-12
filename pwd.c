/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:20:09 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/12 16:02:19 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(int fd, char **envp)
{
	//char	*tmp;
	//char	*pwd;

	//tmp = return_env_line(envp, search_part_line(envp, "PWD=", 4));
	//pwd = ft_substr(tmp, 4, ft_strlen(tmp) - 4);
	//free(tmp);
	//ft_putstr_fd(pwd, fd);
	(void) envp;
	ft_putstr_fd(getcwd(NULL, 0), fd);
	ft_putchar_fd('\n', fd);
	//free(pwd);
}
