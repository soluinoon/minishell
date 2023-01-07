/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <jihonkim@42student.42seoul.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:22:22 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/07 17:06:58 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_token *token)
{
	t_env_list	*env_list;
	char		*prev_pwd;
	char		*cur_pwd;
	char		*tmp;

	env_list = token->info->env_list;
	tmp = ft_calloc(4096, sizeof(char));
	if (!tmp)
		throw_error(MALLOC_ERR);
	prev_pwd = ft_getenv(env_list, "PWD");
	cur_pwd = getcwd(tmp, 4096);
	ft_putenv(env_list, "PWD", cur_pwd, 0);
	ft_putenv(env_list, "OLDPWD", prev_pwd, 0);
	free(tmp);
	free(prev_pwd);
}

static void	if_cd_home(t_token *token, char *home_path)
{
	if (ft_strncmp(home_path, "", 1) == 0)
	{
		throw_error_message("cd", NULL, "HOME not set", 1);
		token->info->exit_num = 1;
	}
	else if (chdir(home_path) == -1)
	{
		throw_error_message("cd", home_path, \
		"No such file or directory", 1);
		token->info->exit_num = 1;
	}
	else
		token->info->exit_num = 0;
}

void	ft_cd(t_token *token)
{
	t_env_list	*env_list;

	env_list = token->info->env_list;
	if (token->cmd[1])
	{
		if (ft_strncmp(ft_getenv(env_list, "HOME"), "", 1) == 0 && \
		ft_strncmp(token->cmd[1], "", 1) == 0)
		{
			throw_error_message("cd", NULL, "HOME not set", 1);
			token->info->exit_num = 1;
		}
		else if (chdir(token->cmd[1]) == -1)
		{
			throw_error_message("cd", token->cmd[1], \
			"No such file or directory", 1);
			token->info->exit_num = 1;
		}
		else
			token->info->exit_num = 0;
	}
	else
		if_cd_home(token, ft_getenv(env_list, "HOME"));
	update_pwd(token);
}
