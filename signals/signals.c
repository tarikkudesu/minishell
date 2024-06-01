/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:26:37 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/04/05 13:52:32 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_sig;

int	ctrl_c_exit_status(int __status, int __flag)
{
	static int	old_status;

	if (__flag == 1)
		old_status = 1;
	else
		old_status = __status;
	return (old_status);
}

void	sig_h(int sig)
{
	if (sig)
		g_sig = 1;
	close(0);
}

void	ctl_c(int signal)
{
	if (signal == SIGINT && g_sig != -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		ctrl_c_exit_status(1, 1);
		g_sig = 1;
		close(0);
	}
}

void	signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctl_c);
	signal(SIGQUIT, SIG_IGN);
}
