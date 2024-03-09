/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:15:56 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/07 23:49:26 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process(t_shell *data, t_tokens *token, int input, int output)
{
	static int i;
	if (data || token || input || output)
		puts("coming soon...");
	printf("-----%d-----\n", getpid());
	if (dup2(input, STDIN_FILENO) < 0 || dup2(output, STDOUT_FILENO) < 0)
		ft_throw("DUP2_CHILD_ERROR");
	if (close(input) < 0 || close(output) < 0)
		ft_throw("CLOSE_CHILD_ERROR");
	exit(++i);
}