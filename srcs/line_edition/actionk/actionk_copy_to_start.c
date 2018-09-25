/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:41:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:34:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**  Copy the part of command line that is before the cursor, into the shell
**  clipboard. If the 'part of line' is empty (cursor is on the start-position 
**	of the command line), it clears the clipboard.
**  The character under the cursor is not copied.
*/

void    actionk_copy_to_start(struct s_line *le)
{
	le->clipboard_len = 0;
	check_clipboard_storage(le, le->cursor_index + 1);

	le->clipboard[0] = '\0';
	ft_strncat( le->clipboard, &(le->cmd[0]), le->cursor_index );
   // fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
