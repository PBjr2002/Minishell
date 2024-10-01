/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/01 17:40:48 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"


// this file will contain a compilation of errors which require fixing, please include the result and bash result in the examples, like this:
//
// $?
// NOSSO = 0
// BASH = 0

/*
------------------------------------------------------------------
	
	
	
	------------------------------------------------------------------
	
	ao executar /bin/ls (invalid file), seguido de echo $?

	nosso = 0
	bash = 2
	
	------------------------------------------------------------------
	
	ao executar iiiii, seguido de echo $?

	nosso = 0
	bash = 127
	
	------------------------------------------------------------------
	
	ao executar heredocs, os inputs do heredoc nao sao expandidos

	nosso = cat << $USER
	>$HOME
	>$USER
	$HOME
	
	bash = cat << $USER
	>$HOME
	>$USER
	/home/lmiguel-
	
	------------------------------------------------------------------

	ao fazer export de variaveis com espacos, estes sao ignorados.
	isto leva a problemas quando a variavel exportada e usada como comando:

	export hey="ls -a"
	$hey

	nosso = ls -a: command not found
	bash = .  ..  .git  inc  makefile  minishell  obj  README.md  src  sup_readline.supp

	(solucao simples, basta efetuar uma especie de split e incrementar uma vez todos os elementos da lista de tokens, "empurrar uma vez na direcao do fim")

	------------------------------------------------------------------
	
	export nao esta a ser feito corretamente
	export hey="ls -l"
	env

	nosso env = hey=
	bash env = hey=ls -l
	
	------------------------------------------------------------------

	duplo heredoc esta a dar um erro
	cat <<out1 | cat <<out2
	>123
	>out1
	>321
	>out2
	
	nosso = There was an error duplicating the FD
	bash = 321
	
	------------------------------------------------------------------

	ao enviar apenas uma redirecao, o programa nao a executa
	<<here

	nosso = here: no such file or directory
	bash = (abre heredoc)

	>out
	nosso = out: no such file or directory
	bash = (abre ficheiro chamado out)
	
	------------------------------------------------------------------

	o comando echo nao imprime as flags se estas forem invalidas

	echo -nnn -nnnnnngnnnnnn -nnnnnnnnnn kljh

	nosso = kljh
	bash = -nnnnnngnnnnnn -nnnnnnnnnn kljh
	
	------------------------------------------------------------------

	ao enviar varias redirecoes num so comando, apenas a primeira e aberta (?)
	ls >1>2

	nosso = apenas o "1" e aberto, e contem a informacao
	bash = abre o 1 e o 2, com a informacao presente apenas no 2
	
	------------------------------------------------------------------

	
	
	------------------------------------------------------------------
	
*/