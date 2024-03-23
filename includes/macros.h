/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:17:12 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 21:43:11 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define ERR_ARG				"minishell error : no arguments required "
# define ERR_NOT_VALID			"minishell error : not a valid identifier"
# define ERR_CMD_NOT_FOUND		"minishell error : command not found "
# define ERR_UNCLOSED_QUOTES	"minishell error : unclosed quotes "
# define ERR_MAL				"minishell error : malloc "
# define ERR_UNLINK				"minishell error : unlink "
# define ERR_EXECVE				"minishell error : execve "
# define ERR_SYNTAX 			"minishell : syntax error "
# define ERR_FORK				"minishell error : fork "
# define ERR_PIPE				"minishell error : pipe "
# define ERR_DUP2				"minishell error : dup2 "
# define ERR_OPEN				"minishell error : open "
# define ERR_DUP				"minishell error : dup "
# define ERR					"minishell error "

#endif