/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:51:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/06 20:13:36 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tests.h"
#include <time.h>

struct s_cmd_status	g_cmd_status = {
	.cmd_running = false, .keep_le_cmd = NULL, .resize_happened = false, .sigint_happened = false
};

t_job	*g_jobs;

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{"v", "-verbose"}, "Enable verbose mode", false},
	{{NULL}, NULL, false}
};

t_environ		*g_envp;
/*
static void		init_shell_vars(char **env, t_shell_vars *vars)
{
	static t_environ			env_vars;
	static t_local_vars			local_vars;
	static t_internal_vars		internal_vars;
	char						*ret_itoa;

	vars->env = &env_vars;
	vars->locals = &local_vars;
	vars->internals = &internal_vars;
	init_environ(env, vars->env);
	init_environ_struct_ptrs(&local_vars);
	init_environ_struct_ptrs(&internal_vars);
	if ((ret_itoa = ft_itoa(getpid())) == NULL)
		exit(MALLOC_ERROR);
	internal_vars.add_var(&internal_vars, "$", ret_itoa);
	free(ret_itoa);
	internal_vars.add_var(&internal_vars, "!", "0");
	internal_vars.add_var(&internal_vars, "42SH_VERSION", "0.0.42");
	if ((ret_itoa = ft_itoa(getuid())) == NULL)
		exit(MALLOC_ERROR);
	internal_vars.add_var(&internal_vars, "UID", ret_itoa);
	free(ret_itoa);
	internal_vars.add_var(&internal_vars, "IFS", IFS);
} */
/*
char		*get_valid_input(t_lexeme **lexemes, int sub_prompt)
{
	char		*input;
	char		*unmatched_quote_err_ptr;
	t_lexeme	*lexemes_ret;

	input = RESIZE_IN_PROGRESS;
	while (input == RESIZE_IN_PROGRESS)
		input = line_edition(sub_prompt);
	if (g_cmd_status.resize_happened == false)
		ft_putchar('\n');
	while (lexer(input, &lexemes_ret, &unmatched_quote_err_ptr) == \
	UNMATCHED_QUOTE_ERR)
	{
		free_lexemes(lexemes_ret);
		if (!subpp_string(&input))
			return (NULL);
	}
	*lexemes = lexemes_ret;
	return (input);
} */

int	main(int argc, char **argv, char **envp)
{
    clock_t 	start, end;
	id_t		backup_stdout, backup_stderr;
	(void)argc;
	(void)argv;
	(void)envp;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	init_shell_vars(envp, get_shell_vars());
	t_environ	*env = get_shell_vars()->env;
	init_signals();
	//builtin_env((char *[2]){"env", NULL}, env, NULL);
	g_sh_opts[1].opt_status = true;
	/*backup_stdout = dup(STDOUT_FILENO);
	backup_stderr = dup(STDERR_FILENO);*/

	//start = clock();
	lexer_tests(env);
	ast_tests(env);
	builtins_tests(env);
	exec_tests(env);
	syntax_highlighting_tests(env);
	script_tests(env);
	builtin_test_tests(env);

	/*
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	dup2(backup_stderr, STDERR_FILENO);*/

	printf("Some particular tests with pipes cannot be automatized as they require interactive mode,\nbefore pushing to the main branch, please be sure that the following tests have the same behavior on "SH_NAME" and sh:\n\
		\tcat | ls\n\
		\tcat | cat -e\n\
		\tdoesnotexits | cat\n");
	done_testing();
	//end = clock();

    //printf("Took %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
}
