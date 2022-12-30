/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:42:08 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:13:13 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd, t_token *token)
{
	int	i;
	int	n_flag;

	n_flag = 1;
	i = 1;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		n_flag = 0;
		i = 2;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (n_flag)
		printf("\n");
	token->info->exit_num = 0;
}
