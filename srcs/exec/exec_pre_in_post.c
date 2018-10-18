/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/18 16:56:41 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** In use for return of keyword BREAK and CONTINUE.
** Check if the code is inside an inner while.
*/

static int		look_for_loop_node(t_ast *node, int statement)
{
	while (node && node->type_details != TK_SCRIPT_WHILE)
	{
		if (node && node->top_ast)
			node = node->top_ast;
		else
			node = node->parent;
	}
	if (node && node->type_details == TK_SCRIPT_WHILE)
	{
		if (statement == TK_SCRIPT_BREAK)
			return (STATEMENT_BREAK);
		if (statement == TK_SCRIPT_CONTINUE)
			return (STATEMENT_CONTINUE);
	}
	return (0);
}

/*
** Distribute the **argv to the rigth processing function
*/

void	exec_argv(char **argv, char **envp, t_exec *exe, t_ast *node)
{
	int		not;

	not = 0;
	if (ft_strequ(argv[0], "!") && argv[1])
	{
		not = 1;
		argv++;
	}
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, envp, exe, node);
	else if (!exec_builtin(argv, envp, exe, node))
		if (exec_binary(argv, envp, exe, node) == STATEMENT_NOCMD)
			exe->ret = -1;
	if (not)
		exe->ret = (exe->ret == 0) ? 1 : 0;
}

/*
** Is executed at the first passage of a node in the AST
*/

t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}

/*
** Is executed at the second passage of a node in the AST
*/

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	char	**envp;

	if (!node->data)
		return (exe);
	log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	if (node->type == T_SCRIPT_STATEMENT && !exe->ready_for_exec)
	{
		exe->statement = look_for_loop_node(node, node->type_details);
		if (exe->statement)
			return (exe);
	}
	if (node->sub_ast)
	{
		script_in_exec(node->sub_ast, exe);
		if (exe->statement && node->sub_ast->left && \
		node->sub_ast->left->type_details != TK_SCRIPT_WHILE)
			return (exe);
		else
			exe->statement = 0;
	}
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
	{
		io_manager_in(node, exe);
		log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	}
	if (((node->type == T_WORD && node->type_details == TK_DEFAULT) || node->type_details == TK_SCRIPT_CONDITION_IF || node->type_details == TK_SCRIPT_CONDITION_WHILE) && !exe->ready_for_exec)
	{
		if (exe->tmp_envp)
			envp = exe->tmp_envp;
		else
			envp = exe->envp;
		if (!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
			exec_argv(node->data, envp, exe, node);
	}
	return (exe);
}

/*
** Is executed at the third and last passage of a node in the AST
*/

t_exec	*post_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}
