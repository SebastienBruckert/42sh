/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:45:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/01 11:27:38 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	is_expansion_end_char(char c)
{
	if (c == '$' || c == '\\' || \
		c == '\'' || c == '"' || \
		c == '/' || is_separator(c))
		return (1);
	return (0);
}

char		*get_expansion_end(char *str)
{
	char		*r;

	r = str + 1;
	while (*r && !is_expansion_end_char(*r))
		r++;
	log_fatal("expansion end |%s|", r);
	return (r);
}
