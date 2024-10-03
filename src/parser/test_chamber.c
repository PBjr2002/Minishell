/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chamber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/03 16:32:31 by lmiguel-         ###   ########.fr       */
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
	>"$USER"
	>'$USER'
	>$USER
	$HOME
	"$USER"
	'$USER'
	
	bash = cat << $USER
	>$HOME
	>"$USER"
	>'$USER'
	>$USER
	/home/lmiguel-
	"lmiguel-"
	'lmiguel-'

	bash = cat << ""$USER ou "$USER" ou "$"USER etc...
	>$HOME
	>"$USER"
	>'$USER'
	>$USER
	$HOME
	"$USER"
	'$USER'
	
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

	
	ao executar um numero elevado de pipes ao mesmo tempo, o programa 
	nao os fecha corretamente

	echo 123 | cat | cat

	pipes abertos excede os 3 STD e apresenta o erro:
	There was an error duplicating the FD
	|
	
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


	se varias flags forem fornecidas ao echo, o valgrind alerta para varios
	invalid reads no exec_echo (size 1)
	
	------------------------------------------------------------------

	ao enviar varias redirecoes num so comando, apenas a primeira e aberta
	ls >1>2

	nosso = apenas o "1" e aberto, e contem a informacao
	bash = abre o 1 e o 2, com a informacao presente apenas no 2
	
	------------------------------------------------------------------

	bug condicional de export:
	se o comando inicial de um export for apenas uma variavel sem igual,
	em usos sucessivos de export, a variavel nao levara update ao executar env

	export a
	a
	export a=b
	env
	
	nosso = (a nao existe)
	bash = a=b
	
	------------------------------------------------------------------
	
	bug no export:
	se uma environment variable comecar por underscore, esta nao e adicionada
	ao env caso o export for executado. a variavel

	export _gofas=z
	env

	nosso = (_gofas nao existe)
	bash = _gofas=z
	
	------------------------------------------------------------------
	
	heredoc nao aceita ctrl + d e executa o ctrl + c incorretamente
	
	cat << eof
	>ewewe
	ctrl + c

	nosso = exitshell> ^C
			ewewe
			Hellshell>
		
	
	------------------------------------------------------------------

	se mandarmos o input ./././././././. ou /////////////// para o minishell,
	este apresenta um erro "Permission denied"

	./././././././././
	
	nosso = Permission denied
	bash = ./././././././././ : is a directory.
	
	
	------------------------------------------------------------------
*/