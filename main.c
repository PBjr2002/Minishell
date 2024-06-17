/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:56:06 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/17 13:58:39 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_parser	*info;
	int		len;
	int		n;

	n = 0;
	len = 0;
	info = malloc(sizeof(t_parser));
	info->env = copy_env(envp);
	prompt(ac, av, info);
	return (0);
}
