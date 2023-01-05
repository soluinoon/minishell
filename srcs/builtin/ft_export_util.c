/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <jihonkim@42student.42seoul.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:31:59 by kko               #+#    #+#             */
/*   Updated: 2023/01/05 13:03:36 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_util(t_token *token, int *flag, char **key, char **value)
{
	if (*flag == SUCCESS)
	{
		ft_putenv(token->info->env_list, *key, *value, 0);
		if (ft_strncmp(*key, "HOME", 5) == 0)
			ft_putenv(token->info->env_list, "~", *value, 0);
	}
	else if (*flag == 2)
	{
		ft_putenv(token->info->env_list, *key, *value, 1);
	}
	token->info->exit_num = 0;
}
