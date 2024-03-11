#include "includes/minishell.h"

int meta_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\v' || c == '\f' \
		|| c == '>' || c == '<' || c == '|' \
		|| c == '"' || c == '\'' || c == '$')
		return (1);
	return (0);
}

char    *re_meta_char_string(char *string, int *index)
{
	int	len;

	if (*string == ' ' || *string == '\t' || *string == '\n' \
		|| *string == '\r' || *string == '\v' || *string == '\f' \
		|| *string == '|' || *string == '"' || *string == '\'')
	{
		(*index)++;
		return (ft_substr(string, 0, 1));
	}
	else if ((*string == '<' && *(string + 1) == '<') \
		|| (*string == '>' && *(string + 1) == '>'))
	{
		(*index) += 2;
		return (ft_substr(string, 0, 2));
	}
	else if (*string == '>' || *(string + 1) == '<')
	{
		(*index) += 1;
		return (ft_substr(string, 0, 1));
	}
	else if (*string == '$')
	{
		len = 1;
		while (*(string + len) && !meta_char(*(string + len)))
			len++;
		(*index) += len;
		return (ft_substr(string, 0, len));
	}
	return (NULL);
}

void    re_token_type(t_shell *data, t_tokens *token)
{
	if (!ft_strcmp(token->string, "|"))
		token->type = RE_PIPE;
	else if (!ft_strcmp(token->string, "'"))
	{
		token->type = QUOTE;
		if (data->stat == INQUOTE)
			data->stat = GENERAL;
		else
			data->stat = INQUOTE;
	}
	else if (!ft_strcmp(token->string, "\""))
	{
		token->type = DQUOTE;
		if (data->stat == INDQUOTE)
			data->stat = GENERAL;
		else
			data->stat = INDQUOTE;
	}
	else if (!ft_strcmp(token->string, ">>"))
		token->type = RE_APPEND;
	else if (!ft_strcmp(token->string, "<<"))
		token->type = RE_HEREDOC;
	else if (!ft_strcmp(token->string, "<"))
		token->type = IN_RED;
	else if (!ft_strcmp(token->string, ">"))
		token->type = OUT_RED;
	else if (!ft_strcmp(token->string, " "))
		token->type = WHITESPACE;
	else if (!ft_strncmp(token->string, "$", 1))
		token->type = ENV;
	else
		token->type = RE_WORD;
}

char    *re_token_string(char *string, int *index)
{
	int     i;
	char    *word;

	i = 0;
	if (!meta_char(*string))
	{
		while (*(string + i) && !meta_char(*(string + i)))
			i++;
		(*index) += i;
		word = ft_substr(string, 0, i);
		if (!word)
			return (NULL);
		return (word);
	}
	return (re_meta_char_string(string, index));
}

t_tokens    *re_init_token(t_shell *data, char *line, int *index)
{
	char        *string;
	t_tokens    *token;

	string = re_token_string(line + *index, index);
	if (!string)
		return (NULL);
	token = tokennew(string);
	if (!token)
		return (NULL);
	re_token_type(data, token);
	token->stat = data->stat;
	return (token);
}

int	lexer_redone(t_shell *data)
{
	int			i;
	int			index;
	t_tokens    *token;

	i = 0;
	index = 0;
	while (data->line[index])
	{
		i++;
		token = re_init_token(data, data->line, &index);
		if (!token)
			return 1;
		token->index = i;
		tokenadd_back(&data->cherry, token);
	}
	return (0);
}
