/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_mem_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:05:31 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/11 14:17:48 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	free_tab(char **items)
{
	int	i;

	i = 0;
	while (items && items[i])
	{
		free(items[i]);
		items[i] = NULL;
		i++;
	}
	free(items);
}
