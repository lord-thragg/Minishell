/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:43:29 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/14 12:12:18 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_exit_argument(char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalpha(arg[i]))
		{
			free_all(shell, "exit\nExit: Numeric argument required\n", 2);
		}
		i++;
	}
}

int	ft_exit(t_shell *shell)
{
	int	ecode;
	int	i;

	i = 0;
	while (shell->cmd->cmd_list[i])
		i++;
	if (i > 2)
		return (printf("Exit: too many arguments\n"));
	if (shell->cmd->cmd_list[1])
	{
		check_exit_argument(shell->cmd->cmd_list[1], shell);
		ecode = ft_atoi(shell->cmd->cmd_list[1]);
		if (shell->cmd)
			shell->cmd = free_cmd(shell->cmd);
		if (shell->env)
			ft_freetab(shell->env);
		rl_clear_history();
		printf("exit\n");
		exit(ecode);
	}
	else
		free_all(shell, "exit\n", 0);
	return (0);
}
