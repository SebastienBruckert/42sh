/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_assigns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:02:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/10 20:02:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_environ	*get_env_to_use(t_exec *exe, char ***tmp_env_assigns_begin)
{
	t_shell_vars	*vars;

	*tmp_env_assigns_begin = NULL;
	if (!(vars = get_shell_vars()))
		return (NULL);
	*tmp_env_assigns_begin = \
		vars->env->last_entry_ptr->ptr_to_pos_in_environ_tab + 1;
	return (vars->env);
}

char		**handle_env_assigns(t_ast *node, t_exec *exe)
{
	t_environ	*env_to_use;
	char		*tmp;
	char		**tmp_env_assigns;

	(void)exe;
	if (!(node && node->left && node->left->type == T_ENV_ASSIGN))
		return (NULL);
	tmp_env_assigns = NULL;
	while (node->left)
		node = node->left;
	log_info("PID %zu: Handle env assigns of %s(t %d td %d)", getpid(), node->data[0], \
		node->type, node->type_details);
	env_to_use = get_env_to_use(exe, &tmp_env_assigns);
	//env_to_use = get_shell_vars()->env;
	while (node->type == T_ENV_ASSIGN)
	{
		if (!(env_to_use->get_var(env_to_use, node->data[0])))
			env_to_use->add_var(env_to_use, node->data[0], NULL);
		else
		{
			tmp = ft_strchr(node->data[0], '=');
			ft_strncpy(env_to_use->last_used_elem->val_begin_ptr, tmp + sizeof(char), \
				MAX_ENV_ENTRY_LEN - ((tmp - node->data[0]) * sizeof(char)));
		}
		node = node->parent;
	}
	return (tmp_env_assigns);
}
