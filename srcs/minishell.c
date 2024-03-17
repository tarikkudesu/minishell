
#include "../includes/minishell.h"

void	minishell(t_shell *data)
{
	if (lexer(data))
		return ;
	if (pars(data))
		return ;
	if (syntax(data))
        return ;
	// fonction_mli7a(data);
	command_tree(data);
	execute(data);
    if (data->number_of_commands > 1)
        (free_2d_int(data->pipes, data->number_of_commands - 1), \
        data->pipes = NULL);
}

void	read_line(t_shell *data)
{
	char	*line;

	while (1)
	{
		rl_initialize();
		line = readline("\033[1;32m➜  \033[1;36mminishell \033[0m");
		if (!line)
			return ;
		if (*line)
		{
			add_history(line);
			data->line = line;
			data->stat = GENERAL;
			minishell(data);
			(clear_command_tree(&data->tokens), data->tokens = NULL);
			(clear_command_tree(&data->tree), data->tree = NULL);
		}
		free(line);
		line = NULL;
		data->line = NULL;
	}
}
