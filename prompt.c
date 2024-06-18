/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/18 15:53:26 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(int ac, char **av, t_parser *info)
{
	char	*input;
	char	**new_av;
	int		new_ac;
	
	(void) ac;
	(void) av;
	while (1)
	{
		new_ac = 0;
		input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m");
		new_av = ft_split(input, ' ');
		if (input && input[0])
			add_history(input);
		free(input);
		if (new_av && new_av[0])
		{
			while (new_av[new_ac])
				new_ac++;
			decider(new_ac, new_av, info);
			new_ac = 0;
			while (new_av[new_ac])
			{
				free(new_av[new_ac]);
				new_ac++;
			}
			free(new_av);
		}
	}
}
