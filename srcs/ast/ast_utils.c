/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:47:09 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/21 18:10:48 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

inline int	is_op0(t_lexeme *lex)
{
	return (lex->type_details == TK_AND
	|| lex->type_details == TK_SEMICOLON
	|| lex->type_details == TK_NEWLINE);
}

inline int	is_op1(t_lexeme *lex)
{
	return (lex->type_details == TK_DAND
	|| lex->type_details == TK_OR);
}

inline int	is_op2(t_lexeme *lex)
{
	return (lex->type_details == TK_PIPE
	|| (lex->type == T_REDIR_OPT
		&& lex->type_details != TK_DLESS
		&& lex->type_details != TK_DLESSDASH));
}

inline int	is_op3(t_lexeme *lex)
{
	return (lex->type_details == TK_DLESS
	|| lex->type_details == TK_DLESSDASH);
}
