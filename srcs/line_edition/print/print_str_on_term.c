/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_on_term.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 21:18:37 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 18:20:31 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Print a string on the terminal's window, using the cursor position 
**	'tmp_current_cursor_pos'. The parameter 'foo' is a value depending of the
**	situation when the function is used. This is very ugly but I do not want to 
**	rebuild this feature, it works well.
*/

unsigned int	print_str_on_term(const char *str,
								  unsigned int tmp_cursor_pos,
								  struct s_line *le, int foo)
{
	bool foofoo; 
	
	foofoo = false;
	if (foo == LE_SPECIAL_CASE)
	{
		foo = 2;
		foofoo = true;
	}
	while (*str != '\0')
	{
		++tmp_cursor_pos;
		if (tmp_cursor_pos - foo == le->term_line_size - 1)
		{
			tputs(le->tcaps->_do, 1, &write_one_char);
			cursor_crosses_screen(le, CROSS_TO_LEFT);
			tmp_cursor_pos = 0;
			if (foofoo == true)
			{
				foo = 1;
				foofoo = false;
			}
		}
		print_key(*str);
		++str;
	}
	return (tmp_cursor_pos);
}