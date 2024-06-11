/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/11 13:03:48 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(int ac, char **av, char **envp)
{
	char	*input;
	char	**new_av;
	int		new_ac;
	
	(void) ac;
	(void) av;
	while (1)
	{
		new_ac = 0;
		input = readline("Hellshell$ ");
		new_av = ft_split(input, ' ');
		free(input);
		while (new_av[new_ac])
			new_ac++;
		decider(new_ac, new_av, envp);
		new_ac = 0;
		while (new_av[new_ac])
		{
			free(new_av[new_ac]);
			new_ac++;
		}
		free(new_av);
	}
}
