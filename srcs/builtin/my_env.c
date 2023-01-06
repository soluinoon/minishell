/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:08:29 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/06 15:25:15 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_token *token)
{
	t_env_list	*env_list;

	env_list = token->info->env_list;
	if (get_sec_arr_len(token->cmd) > 1)
	{
		token->info->exit_num = 1;
		throw_error_message("exit", NULL, "too many arguments", 1);
		return ;
	}
	token->info->exit_num = 0;
	print_envs(token->info->env_list);
}
