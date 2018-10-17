/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:38:32 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/16 15:24:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Recursive. print the tree form left to right
*/

static void	print_arg(t_ast *node)
{
	int		i;

	i = 0;
	while (node->data[i])
	{
		if (node->data[i + 1])
			ft_printf("\e[1m%s ", node->data[i]);
		else if (node->type_details == TK_PIPE)
			ft_printf("\e[1m%s\e[0m - (out: %d - in: %d)\e[2m - %p\e[0m\n", node->data[i], node->data[1][0], node->data[1][sizeof(int)], node);
		else
			ft_printf("\e[1m%s\e[0m - \e[2m - %p\e[0m\n", node->data[i], node);
		i++;
	}
}

static void	print_subast(t_ast *node, int *sub_level)
{
	int			sl;

	sl = 0;
	(*sub_level)++;
	while (sl++ < *sub_level)
		ft_printf("\e[2m------->\e[0m");
	ft_printf("=================== SUB_AST ===================\n");
	print_ast_tree(node->sub_ast, 0);
	sl = 0;
	while (sl++ < *sub_level)
		ft_printf("\e[2m------->\e[0m");
	ft_printf("===============================================\n");
	(*sub_level)--;
}

void		print_ast_tree(t_ast *node, int level)
{
	int			l;
	int			sl;
	static int	sub_level = 0;

	l = level;
	if (!node)
		return ;
	sl = 0;
	print_ast_tree(node->right, level + 1);
	while (sl++ < sub_level)
		ft_printf("\e[2m------->\e[0m");
	while (l-- > 0)
		ft_putchar('\t');
	if (node->data && node->data[0] && node->data[0][0] == '\n')
		ft_printf("\e[1m\\n\e[0m \e[2m - %p\e[0m\n", node);
	else if (node->data && node->data[0])
		print_arg(node);
	else
		ft_printf("\e[1m%c\e[0m \e[2m%p - \e[0m\n", '~', node);
	if (node->sub_ast && node->data)
		print_subast(node, &sub_level);
	print_ast_tree(node->left, level + 1);
}

/*
** Main function for printing and showing the tree from the root
*/

void		ast_debug(t_ast *root)
{
	if (root)
		print_ast_tree(root, 0);
}
