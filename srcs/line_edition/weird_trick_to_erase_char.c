/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_trick_to_erase_char.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:06:05 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/02 18:06:42 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	weird_trick_to_erase_char(struct s_line *le)
{
	write(STDOUT_FILENO, " ", sizeof(char));
	tputs(le->tcaps->le, 1, &write_one_char);
	tputs(le->tcaps->nd, 1, &write_one_char);
}
