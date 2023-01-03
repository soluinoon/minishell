/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:20:58 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/03 14:16:29 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	can_be_exit_num(char *num)
{
	int	i;
	int	flag;

	flag = SUCCESS;
	i = 0;
	if (!num)
		return (FAIL);
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			flag = FAIL;
		i++;
	}
	return (flag);
}

void	ft_exit_with_print(t_token *tok, char **cmd)
{
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, tok->info->old_term);
	exit(tok->info->exit_num);
}

void	ft_exit(t_token *tok, char **cmd)
{
	if (cmd[1] == NULL)
	{
		ft_exit_with_print(tok, cmd); // 이게 맞나?
	}
	else if (can_be_exit_num(cmd[1]) == 1)
	{
		if (cmd[2] != 0)
		{
			tok->info->exit_num = 1;
			throw_error_message("exit", NULL, "too many arguments", 1);
		}
		else
		{
			printf("exit\n");
			tcsetattr(STDIN_FILENO, TCSANOW, tok->info->old_term);
			exit(ft_atoi(cmd[1]));
		}
	}
	else
	{
		printf("exit\n");
		throw_error_message("exit", cmd[1], "numeric argument required", 255);
		tcsetattr(STDIN_FILENO, TCSANOW, tok->info->old_term);
		exit(255);
	}
}
