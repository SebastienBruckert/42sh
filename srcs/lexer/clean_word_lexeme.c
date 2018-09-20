/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_word_lexeme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:18:07 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 18:28:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Returns 1 if *s character should be removed or not
** $s: data string
** $i: pos in string
** $jump_ptr: set to ptr to position of corresponding quote if passed argument
**            != NULL
*/

static int		is_quote_removable(char *s, char **jump_ptr,
				int *quote_type)
{
	char	*tmp;
	char	c;
	char	*ptr;

	tmp = NULL;
	ptr = s;
	c = *ptr;
	if ((tmp = has_matching_quote(ptr, c)))
	{
		if (jump_ptr)
			*jump_ptr = tmp;
		log_debug("Found removable quote @ : |%s|", tmp);
		if (c == '"')
			*quote_type = IN_DQUOTES;
		else if (c == '\'')
			*quote_type = IN_SQUOTES;
		return (1);
	}
	return (0);
}

/*
** Returns 1 if c is an expansion specifier char and store handler
** in *callback,
** otherwise return 0
*/

static int		is_expansion_char(char c, void **callback)
{
	*callback = NULL;
	if (c == '$')
		*callback = handle_dollar_expansion;
	/*else if (c == '~')
		*callback = handle_tild_expansion;*/
	return ((*callback) ? (1) : (0));
}

/*
** Fills new created data string
** $s: old data string
** $new_data: ptr to new data string
*/

static void		fill_new_data_str(t_lexeme_data_to_clean *l)
{
	char	*ptr;
	int		in_quote_type;
	char	*jump_ptr;
	void	*expansion_handler;

	ptr = l->raw_lexeme_data;
	l->raw_lexeme_read_ptr = &ptr;
	jump_ptr = ptr;
	while (ptr && *ptr)
		if (is_expansion_char(*ptr, &expansion_handler))
			(*(void (*)(t_lexeme_data_to_clean *, char **))(expansion_handler))\
				(l, g_envp);
		else if (*ptr == '\\')
		{
			ptr += sizeof(char) * handle_escape_offset(ptr, NOT_IN_QUOTES);
			(*(l->new_data_write_ptr++)) = *(ptr++);
		}
		else if ((*ptr == '\'' || *ptr == '"') && \
			is_quote_removable(ptr, &jump_ptr, &in_quote_type))
		{
			ptr++;
			while (*ptr && ptr != jump_ptr)
			{
				if (*ptr == '\\')
					ptr += \
						sizeof(char) * handle_escape_offset(ptr, in_quote_type);
				(*(l->new_data_write_ptr++)) = *(ptr++);
			}
			if (*ptr)
				ptr++;
		}
		else
			(*(l->new_data_write_ptr++)) = *(ptr++);
	*(l->new_data_write_ptr) = '\0';
}

/*
** Removes ' and " characters from given string by calculating
** count of characters to remove, creating a new string and filling it
** without escaping characters '\' and quotes pairs
*/

void			clean_word_lexeme(char **data)
{
	t_lexeme_data_to_clean	new_lex_data;

	new_lex_data.raw_lexeme_data = *data;
	new_lex_data.new_data_size = ft_strlen(*data) * sizeof(char) + 1;
	new_lex_data.new_data = malloc(new_lex_data.new_data_size);
	new_lex_data.new_data_write_ptr = new_lex_data.new_data;
	log_trace("Filling new cleaned str of |%s|", *data);
	fill_new_data_str(&new_lex_data);
	free(*data);
	*data = new_lex_data.new_data;
	log_debug("Replaced old data w/ |%s|", *data);

}
