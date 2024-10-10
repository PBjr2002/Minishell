/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/10 16:21:03 by lmiguel-         ###   ########.fr       */
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

	se mandarmos o input ./././././././. ou /////////////// para o minishell,
	este apresenta um erro "Permission denied"

	./././././././././
	
	nosso = Permission denied
	bash = ./././././././././ : is a directory.

	(n entendi o problema, a mensagem de erro está lá)
	
	(VER MAIS TARDE, MSG DE ERRO INTERESSA?)
	
	------------------------------------------------------------------

	se apos efetuarmos um comando invalido efetuarmos um comando valido,
	o shell retorna um syntax error

	ls nonexistentdirectory
	
	ls

	nosso : syntax error
	bash : (executa o ls normalmente)

	------------------------------------------------------------------

	ls nao da append a branches corretamente

	ls 'hey'"hey"

	nosso : ls: cannot access 'hey': No such file or directory
			ls: cannot access 'hey': No such file or directory

	bash : ls: cannot access 'heyhey': No such file or directory

	------------------------------------------------------------------

	//ls | grep s >>out | wc <out | cat
	TEST THIS COMMAND FOR LEAKS
*/