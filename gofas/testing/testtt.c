#include "../minishell.h"

t_lexer	*lexer(void)
{
	static t_lexer ola;

	return (&ola);
}