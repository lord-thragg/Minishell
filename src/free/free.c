/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:08:30 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/13 11:27:14 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_all(t_shell *shell, char *emsg, int ecode)
{
	if (shell->env && shell->env[0])
		free_env(shell->env);
	if (shell->token)
		free_token(shell->token);
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (emsg)
		printf("%s", emsg);
	if (ecode != -1)
		exit(ecode);
}
