/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/16 17:32:58 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"


// this file will contain a compilation of errors which require fixing, please include the result and bash result in the examples, like this:
//
// $?
// NOSSO = 0
// BASH = 0
// clear && make re -s && valgrind --suppressions=sup_readline.supp --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell
// clear && make re -s && ./minishell 

/*
	------------------------------------------------------------------

	expansao de argumentos precisa de ignorar espacos
	
	export A="    ls              -la"
	cat $A

	nosso : cat: '    ls              -la': No such file or directory
	bash : cat: 'ls -la': No such file or directory

	n acho que seja problema porque é uma mensagem de erro e o resto do comportamento do comando está igual

	------------------------------------------------------------------
	
	se mandarmos o input ./././././././. ou /////////////// para o minishell,
	este apresenta um erro "Permission denied"

	./././././././././
	
	nosso = Permission denied
	bash = ./././././././././ : is a directory.

	(n entendi o problema, a mensagem de erro está lá)
	
	(VER MAIS TARDE, MSG DE ERRO INTERESSA?)

	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS
*/