/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/20 15:57:22 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(int fd, char **av)
{
	int	n;
	int	i;
	int	nl;

	n = 1;
	i = 1;
	nl = 0;
	while (av[n])
	{
		if (n > 1)
			ft_putchar_fd(' ', fd);
		if (n == 1 && av[n][0] == '-')
		{
			while (av[n][i] && av[n][i] != ' ')
			{
				if (av[n][i] != 'n')
					break ;
				i++;
			}
			if (av[n][i] == ' ' || av[n][i] == '\0')
			{
				nl = 1;
				n++;
			}
		}
		if (av[n])
		{
			ft_putstr_fd(av[n], fd);
			n++;
		}
	}
	if (nl == 0)
		ft_putchar_fd('\n', fd);
}


/* void	expansion(char *av)
{
	char	**split;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	int		i;
	int		n;
	int		k;

	split = ft_split(av, ' ');
	i = 0;
	n = 0;
	k = 0;
	while (split[i])
	{
		while (is_there_$(split[i]))
		{
			while (split[i][n])
			{
				if (split[i][n] == '$')
					break ;				
				n++;
			}
			k = n;
			while (ft_isalnum(split[i][k]))
				k++;
			tmp = ft_substr(split[i], n, k - n);
			tmp2 = ft_substr(split[i], 0, n);
			while (split[i][n])
				n++;
			tmp3 = ft_substr(split[i], k, n - k);
			tmp4 = ft_strjoin(tmp, tmp2);
			free(tmp);
			free(tmp2);
			tmp = ft_strjoin(tmp4, tmp3);
			free(tmp3);
			free(tmp4);
			free(split[i]);
			split[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
} */
