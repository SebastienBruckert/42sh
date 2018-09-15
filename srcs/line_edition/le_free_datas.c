/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_free_datas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 20:35:10 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/15 16:47:11 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	le_free_history(struct s_line *le)
{
	struct s_history	*his;
	struct s_history	*del;

	his = le->history;
	while (his->prev != NULL)
		his = his->prev;

	while (his != NULL)
	{
		free(his->cmd);
		del = his;
		his = his->next;
		free(del);
	}
}

void	le_free_datas(struct s_line *le)
{
	free(le->line);
	free(le->clipboard);
	free(le->save_tmp_cmd);
	le_free_history(le);
}
