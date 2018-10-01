/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:31:07 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/01 11:31:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <twenty_one_sh.h>

/*
** Struct in linked list to store type of lexeme and data pointer
** type: type of lexeme (T_(WORD/CTRL_OPT/REDIR_OPT))
** type_details: token associated with data (TK_(LESS/GREAT/...))
** data: pointer to char * from input to data of element
** elem_(begin/end)_ptr: pointer to beginning and end of lexeme in input string
** next: ptr to next lexeme
*/

typedef struct			s_lexeme
{
	int				type;
	int				type_details;
	void				*data;
	char				*lexeme_begin_ptr;
	char				*lexeme_end_ptr;
	struct s_lexeme		*next;
}						t_lexeme;

/*
** Struct used by clean_word_lexeme()
** to clean a lexeme string of quotes / backslashes,
** and apply expansions.
** raw_lexeme_data: raw lexeme data (before cleaning it)
** new_data: new lexeme data, free of unnecessary quotes/backslashes, w/ expansions
** new_data_size: size of new_data pointer, required for knowing size of
**   new data string size when realloc'ing to store an expansion data
*/

typedef struct			s_lexeme_clean_data
{
	char				*raw_lexeme_data;
	char				**raw_lexeme_read_ptr;
	char				*clean_data;
	char				*clean_data_write_ptr;
	size_t				clean_data_size;
}						t_lexeme_clean_data;

typedef struct			s_ast
{
	size_t			type;
	size_t			type_details;
	char			**data;
	struct s_ast	*sub_ast;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}						t_ast;

/*
** Option typedef:
** an option should be composed of:
** the name of the option: ex: (-)"G" / (--)"--color"
** the description of the option: ex: "Enables colorized output"
** a bool storing its status, initialized with its default value
*/

typedef struct			s_option
{
	char	*opt_name[MAX_OPT_NAMES];
	char	*opt_desc;
	bool	opt_status;
}						t_option;

/*
** Each environnement entry will be stored in a struct with a
** pointer to it's value
** entry: Key/Value pair for environnement entry,
**   like "OLDPWD=something"
** val_begin_ptr: pointer to beginning of value in our key/value pair
**   example, for "OLDPWD=something", val_begin_ptr will point to
**   "something", it allows us not to look for the '=' char
**   everytime we the value of
**   the variable
** ptr_to_pos_in_environ_tab: pointer to t_environ->environ entry position.
**   for not having to search through all variables
**   when we want to delete the entry
*/

typedef struct		s_env_entry
{
	char				entry[MAX_ENV_ENTRY_LEN + 1];
	char				*val_begin_ptr;
	char				**ptr_to_pos_in_environ_tab;
	struct s_env_entry	*prev;
	struct s_env_entry	*next;
}					t_env_entry;

/*
** Environnement struct
** environ: environnement to pass to programs
** last_used_elem: last environnement entry requested / added / updated,
**   set to NULL when calling (del_var) and en entry was deleted
**   example use case in init_environ.c:update_info_env_vars()
**   (mainly used for optimization)
** last_entry_ptr: pointer to last element in our linked list,
**   for way faster element adding
**  env_entries_list: Linked list of env_entry strucs
**  entry_count: Current number of elements in our linked list,
**    also used for speeding up some things while adding/deleting
**    elements
**  add/upt/del/get_var: functions to use to control the linked list
*/

typedef struct		s_environ
{
	char			*environ[MAX_ENV_ENTRIES + 1];
	t_env_entry		*last_used_elem;
	t_env_entry		*last_entry_ptr;
	t_env_entry		*env_entries_list;
	int				entry_count;
	char			*(*add_var)(struct s_environ *, char *, char *);
	char			*(*upt_var)(struct s_environ *, char *, char *);
	int				(*del_var)(struct s_environ *, char *);
	t_env_entry		*(*get_var)(struct s_environ *, char *);
}					t_environ;

/*
** int	ret: the return value of the last command. Default: 0
** int	ready_for_exec: if set to one, next execve() will be bypassed Default: 0
** env: environnement
*/

typedef struct			s_exec
{
	int			ret;
	int			ready_for_exec;
	t_environ	*env;
}						t_exec;


#endif
