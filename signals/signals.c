/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:26:37 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/07 14:42:14 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctl_c(int signal)
{
    if (signal == SIGINT)
	{
    	rl_on_new_line();
    	rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}
void	signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctl_c);
	signal(SIGQUIT, SIG_IGN);
}
