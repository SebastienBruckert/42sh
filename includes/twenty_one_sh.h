/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:15:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/02 11:49:24 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_SH_H
# define TWENTY_ONE_SH_H

# include <stdint.h>
# include <inttypes.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdbool.h>
# include <dirent.h>

# include <errno.h>

# define SH_NAME		"42sh"
# define IFS			"\t\n "
# define MALLOC_ERROR 	1
# define OPT_NOT_FOUND_ERROR 1

# ifndef VERBOSE_MODE
#  define VERBOSE_MODE 0
# endif

# define MAX_OPT_NAMES	2
# define CHAR_OPT_INDEX_SIZE (126)

# define MAX_ENV_ENTRIES	255
# define MAX_ENV_ENTRY_LEN	1024

# include <ft_printf.h>
# include "struct.h"
# include "lexer.h"
# include "log.h"
# include "ast.h"
# include "line_edition.h"
# include "exec.h"
# include "syntax_highlighting.h"
# include "script.h"
# include "get_next_line.h"

# define HISTORY_FILE_PATH "$HOME/.42sh_history"

extern t_option		g_sh_opts[];
extern const int	g_cant_begin_with[];
extern const int	g_token_bypass[];
extern const int	g_tokens[];
extern const int	g_next_tokens[][4];
extern void			(* const g_node_placer[])(t_ast *, t_ast *);
extern const char	*g_prompts[10];

# define SH_USAGE \
	SH_NAME" [-hcGv] [-c \"command\"]"

# define BUILTIN_ENV_USAGE \
	"env [-i][name=value]...	[utility [argument...]]"

# define BUILTIN_CD_USAGE \
	"cd [-L | -P] [-] [directory]"

# define BUILTIN_TEST_USAGE \
	"test, [ --\n\t\ttest expression\n\t\t[ expression ]"

# define BUILTIN_HISTORY_USAGE \
	"Usage : history [n | -d n | --clear | --save]\n"


int			prompt_show(const char *prompt);

void		subp_string(char **s);
t_lexeme	*subp_lexeme(t_lexeme *lex, int need_sub_prompt);
void		subp_heredoc(t_lexeme *lex, char *eof_word);

void		ft_free_argv(char **tab_);

void		init_option_list(t_option **opt_tab, ...);

char		**parse_options(int *ac, char **av, \
				t_option *opt_list, t_option **char_opt_index);

void		format_help(char *usage_str, t_option *opts);

t_option	*get_opt_elem(t_option *opt_list, char *opt_str);

bool		is_option_activated(char *opt_str, \
				t_option *opt_list, t_option **char_opt_index);

char		*add_env_var(t_environ *self, char *name, char *entry_value);

int			del_env_var(struct s_environ *self, char *varname);

t_environ	*get_environ_struct(void);

t_env_entry	*get_env_var(t_environ *self, char *varname);

char	*upd_env_var(t_environ *this, char *name, char *new_value);

t_environ	*init_environ(char **env, t_environ *env_struct);

void	free_env_entries(t_environ *env_struct, t_env_entry *env_entries);

void	free_all_shell_data(void);

void		init_environ_struct_ptrs(t_environ *env_struct);

char	autoc_check_path(char *dirname);

bool		check_history_file(const char *his_file_path);

void	load_history_file(struct s_line *le);

char	*get_parsed_history_file_path(void);

char	*ft_strjoin_path(char *path1, char *path2);

#endif
