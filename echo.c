/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/29 18:03:46 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(int fd, char **av, t_parser *info)
{
	int	n;
	int	i;
	int	nl;
	char *str;

	n = 1;
	i = 1;
	nl = 0;
	//while (av[n])
	//{
	//	if (n > 1)
	//		ft_putchar_fd(' ', fd);
	//	if (n == 1 && av[n][0] == '-')
	//	{
	//		while (av[n][i] && av[n][i] != ' ')
	//		{
	//			if (av[n][i] != 'n')
	//				break ;
	//			i++;
	//		}
	//		if (av[n][i] == ' ' || av[n][i] == '\0')
	//		{
	//			nl = 1;
	//			n++;
	//		}
	//	}
	//	if (av[n])
	//	{
	//		ft_putstr_fd(av[n], fd);
	//		n++;
	//	}
	//}
	//if (nl == 0)
	//	ft_putchar_fd('\n', fd);
	str = exec_expansion(info->env, av[1]);
	ft_putendl_fd(str, fd);
	free(str);
}
