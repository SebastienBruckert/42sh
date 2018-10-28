/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/28 20:08:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Distribute the **argv to the rigth processing function
*/

static void	exec_node(char **argv, t_exec *exe, t_ast *node)
{
	int		not;
	void	(*builtin_fun_ptr)(char **, t_environ *, t_exec *);

	builtin_fun_ptr = NULL;
	not = 0;
	if (ft_strequ(argv[0], "!") && argv[1])
	{
		not = 1;
		argv++;
	}
	if (is_builtin(argv[0], &builtin_fun_ptr))
		exec_thread(\
			(void *[3]){(void *)EXEC_THREAD_BUILTIN, &builtin_fun_ptr, argv}, \
			NULL, exe, node);
	else
		exec_thread((void *[3]){EXEC_THREAD_NOT_BUILTIN, argv[0], argv}, \
			NULL, exe, node);
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
	if (!node->data)
		return (exe);
	if (node->sub_ast)
		script_in_exec(node->sub_ast, exe);
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
		io_manager_in(node, exe);
	if (((node->type == T_WORD && node->type_details == TK_DEFAULT) || \
		node->type_details == TK_SCRIPT_CONDITION_IF || \
		node->type_details == TK_SCRIPT_CONDITION_WHILE) && \
		!exe->ready_for_exec && \
		!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
		exec_node(node->data, exe, node);
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
