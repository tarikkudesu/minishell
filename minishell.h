/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:50 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/01 19:27:37 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <fcntl.h>             //open
#include <stdio.h>             //printf, perror
#include <stdlib.h>            //malloc, free, exit, getenv
#include <unistd.h>            //write, read, access, close, fork, unlink, execve, dup, dup2, pipe, chdir, getcwd, isatty, ttyname, ttyslot
#include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line, rl_replace_line. rl_redisplay, add_history
#include <readline/history.h>  // readline, rl_clear_history, rl_on_new_line, rl_replace_line. rl_redisplay, add_history
#include <signal.h>            //signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/wait.h>          //wait, waitpid, wait3, wait4
#include <sys/stat.h>          //stat, lstat, fstat
#include <dirent.h>            //opendir, closedir
#include <string.h>            //strerror
#include <errno.h>             //errno

#endif