/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_into_cmdline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:08:10 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/02 18:13:38 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	reprint_part_of_line_2(struct s_line *le,
		unsigned int tmp_current_cursor_pos,
		struct s_infos_for_rewriting *infos_rewriting)
{
	unsigned int	i;

	if (tmp_current_cursor_pos == le->li_max_size - 1)
	{
		tputs(le->tcaps->_do, 1, &write_one_char);
		++(infos_rewriting->nb_line_to_go_up);
		i = 0;
		while (i < le->li_max_size - 1)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			++i;
		}
		tmp_current_cursor_pos = 0;
	}
	infos_rewriting->pos_end_rewriting = tmp_current_cursor_pos;
}

static void	reprint_part_of_line(struct s_line *le,
	struct s_infos_for_rewriting *infos_rewriting)
{
	const char		*line;
	unsigned int	tmp_current_cursor_pos;
	unsigned int	i;

	line = (le->line) + (le->cursor_index_for_line);
	tmp_current_cursor_pos = le->current_cursor_pos;
	print_key(*line);
	++line;
	while (*line != '\0')
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - 1 == le->li_max_size - 1)
		{
			tputs(le->tcaps->_do, 1, &write_one_char);
			++(infos_rewriting->nb_line_to_go_up);
			i = 0;
			while (i++ < le->li_max_size - 1)
				tputs(le->tcaps->le, 1, &write_one_char);
			tmp_current_cursor_pos = 0;
		}
		print_key(*line);
		++line;
	}
	reprint_part_of_line_2(le, tmp_current_cursor_pos, infos_rewriting);
}

static void	move_cursor_back_to_right_place(struct s_line *le,
					struct s_infos_for_rewriting *infos_rewriting)
{
	while ((infos_rewriting->nb_line_to_go_up)-- > 0)
		tputs(le->tcaps->up, 1, &write_one_char);
	if (infos_rewriting->pos_end_rewriting < le->current_cursor_pos)
	{
		++(infos_rewriting->pos_end_rewriting);
		if (le->nb_car_written_on_last_current_line == le->li_max_size
		|| (le->current_cursor_line == 0
		&& le->nb_car_written_on_last_current_line == 0))
			--(infos_rewriting->pos_end_rewriting);
		while (infos_rewriting->pos_end_rewriting < le->current_cursor_pos)
		{
			tputs(le->tcaps->nd, 1, &write_one_char);
			++(infos_rewriting->pos_end_rewriting);
		}
	}
	else if (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
	{
		++(infos_rewriting->pos_end_rewriting);
		while ((infos_rewriting->pos_end_rewriting)-- > le->current_cursor_pos)
			tputs(le->tcaps->le, 1, &write_one_char);
	}
	else if (infos_rewriting->pos_end_rewriting == le->current_cursor_pos)
		tputs(le->tcaps->le, 1, &write_one_char);
}

static void	update_values(struct s_line *le)
{
	ft_memmove(le->line + le->cursor_index_for_line - 1, \
		le->line + le->cursor_index_for_line, \
		ft_strlen(le->line + le->cursor_index_for_line));
	le->line[le->line_index - 1] = '\0';
	--(le->line_index);
	if (le->nb_car_written_on_last_current_line == 0)
		le->nb_li_currently_writing -= 1;
	if (le->nb_car_written_on_last_current_line > 0)
		--(le->nb_car_written_on_last_current_line);
	else if (le->nb_car_written_on_last_current_line == 0
	&& le->nb_li_currently_writing > 1)
		le->nb_car_written_on_last_current_line = le->li_max_size - 1;
	if (le->nb_car_written_on_last_current_line == 0)
	{
		if (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1)
			le->nb_car_written_on_last_current_line = le->li_max_size - \
			le->start_pos - 1;
		else
			le->nb_car_written_on_last_current_line = le->li_max_size;
	}
}

void		delete_char_into_cmdline(struct s_line *le)
{
	struct s_infos_for_rewriting	infos_rewriting;

	ft_memset(&infos_rewriting, 0, sizeof(struct s_infos_for_rewriting));
	update_values(le);
	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (le->current_cursor_pos == le->li_max_size - 1)
		weird_trick_to_erase_char(le);
	reprint_part_of_line(le, &infos_rewriting);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (le->nb_car_written_on_last_current_line == le->li_max_size - 1
	&& (le->current_cursor_line + 1) < le->nb_li_currently_writing)
		weird_trick_to_erase_char(le);
	move_cursor_back_to_right_place(le, &infos_rewriting);
	if (le->nb_car_written_on_last_current_line == le->li_max_size
	|| (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1 && 0
	&& le->nb_car_written_on_last_current_line
	== le->li_max_size - le->start_pos))
		le->nb_car_written_on_last_current_line = 0;
}
