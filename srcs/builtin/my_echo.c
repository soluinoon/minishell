/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <jihonkim@42student.42seoul.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:03:34 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/05 15:45:54 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd, t_token *token)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	// echo -n 1 2 3
	while (cmd[i] && ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
		{
			printf(" ");
		}
	}
	if (newline_flag == 1)
		printf("\n");
	token->info->exit_num = 0;
}