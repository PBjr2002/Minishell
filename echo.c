/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/02 12:22:37 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(int fd, char **av, t_parser *info)
{
	int	n;
	int	i;
	int	nl;
	char *str;

	n = 0;
	i = 1;
	nl = 0;
	while (av[++n])
	{
		if (n > 1)
			ft_putchar_fd(' ', fd);
		if (n == 1 && av[n][0] == '-')
		{
			while (av[n][i] && av[n][i] != ' ' && av[n][i] == 'n')
				i++;
			if (av[n][i] == ' ' || av[n++][i] == '\0')
				nl = 1;
		}
		str = exec_expansion(info->env, av[n]);
		ft_putstr_fd(str, fd);
		free(str);
	}
	if (nl == 0)
		ft_putchar_fd('\n', fd);
}
