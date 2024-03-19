/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:17:12 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/19 18:30:28 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define ERR_ARG				"minishell Error : no arguments required"
# define ERR_CMD_NOT_FOUND		"minishell Error : command not found"
# define ERR_UNCLOSED_QUOTES	"minishell Error : unclosed quotes"
# define ERR_MAL				"minishell Error : malloc"
# define ERR_DUP				"minishell Error : dup2"
# define ERR_FORK				"minishell Error : fork"
# define ERR_PIPE				"minishell Error : pipe"
# define ERR_DUP2				"minishell Error : dup"
# define ERR_OPEN				"minishell Error : open"
# define ERR_UNLINK				"minishell Error : unlink"
# define ERR_EXECVE				"minishell Error : execve"
# define ERR_SYNTAX 			"minishell : syntax error"
# define ERR					"minishell Error"

#endif