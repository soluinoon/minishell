/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/02 12:39:46 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_errno;

static t_info	*new_info(void)
{
	t_info	*new;

	new = (t_info *)malloc(sizeof(t_info));
	if (!new)
		throw_error(MALLOC_ERR);
	new->env_list = 0;
	new->old_term = malloc(sizeof(struct termios));
	new->path = 0;
	new->exit_num = 0;
	new->stdio_backup[0] = dup(STDIN_FILENO);
	new->stdio_backup[1] = dup(STDOUT_FILENO);
	return (new);
}

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	(void)ac;
	(void)av;
	g_errno = 0;
	info = new_info();
	initial(info, envp);
	loop(info);
	return (0);
}
