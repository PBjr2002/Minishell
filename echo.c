/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/11 12:54:09 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(int fd, char **av)
{
	int	n;
	int	nl;

	n = 1;
	nl = 0;
	while (av[n])
	{
		if (n > 1)
			ft_putchar_fd(' ', fd);
		if (n == 1 && ft_strcmp(av[n], "-n") == 0)
		{
			nl = 1;
			n++;
		}
		ft_putstr_fd(av[n], fd);
		n++;
	}
	if (nl == 0)
		ft_putchar_fd('\n', fd);
}
