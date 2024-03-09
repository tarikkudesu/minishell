/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/07 00:06:57 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_echo_option(char *option)
{
	int	i;

	i = 0;
	if (option[i] != '-')
		return (0);
	while (option[++i])
	{
		if (option[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_tokens	*echo, char **av)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = echo;
	while (!tmp && av[i])
	{
		// if (is_echo_option(tmp->string)) // decomment it
		if (is_echo_option(av[i])) //to remove (just for test)
			// tmp = tmp->next; // decomment it
			i++; //to remove (just for test)
		else
			break ;
	}
	// while (tmp) // decomment it
	while (av[i]) //to remove (just for test)
		(ft_putstr_fd(av[i], 1), ft_putstr_fd(" ", 1), i++);//to remove (just for test)
		// ft_putstr_fd(tmp->string, 1), ft_putstr_fd(" ", 1), tmp = tmp->next;
}

// int	main(int ac, char **av) // to delete it
// {
// 	if (ac)
// 		ft_echo(NULL, av + 1);
// }