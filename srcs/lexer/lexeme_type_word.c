/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/22 20:38:02 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Search for next (double)quote in string $s
** instead stopping to next $IFS separator
*/

static int	skip_quotes_substring(char *s, int *pos, int start)
{
	char	*quote_pos;

	log_debug("start: |%s|", s + start);
	quote_pos = has_matching_quote(s, start);
	if (!(quote_pos))
	{
		ft_printf("42sh: Error: Unmatched %c\n", s[start]);
		return (1);
	}
	*pos = ((quote_pos - s) / sizeof(char) + sizeof(char));
	log_debug("end: |%s| - %d", s + *pos, *pos);
	return (0);
}

/*
** Parse word operators (default type),
** if string $s do not contains quotes,
** a substring will be made to the next $IFS separator,
** if ' or " characters are found, apply skip_quotes_substring
** to skip $IFS separators until corresponding quote
*/

size_t		lexeme_type_word(char *s, int *pos, char **data)
{
	int		start;

	start = *pos;
	while (s[*pos] && !is_separator(s[*pos]) && !is_operator(s[*pos]))
	{
		if (s[*pos] == '\\')
			*pos += (s[*pos + 1]) ? (2) : (1);
		else if (s[*pos] == '\'' || s[*pos] == '"')
		{
			if (skip_quotes_substring(s, pos, *pos))
				exit(1); // TODO: exit function that frees linked list
		}
		else
			*pos += 1;
	}
	if (start != *pos)
	{
		*data = ft_strsub(s, start, *pos - start);
		if (*data && (ft_strchr(*data, '\'') || ft_strchr(*data, '"') || \
			ft_strchr(*data, '\\')))
			clean_word_lexeme(data);
	}
	else
		*data = NULL;
	if (!(env_assigns_status(0, 0)) && ft_strchr(*data, '='))
		return (T_ENV_ASSIGN);
	env_assigns_status(1, 1);
	return (T_WORD);
}
