/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <jihonkim@42student.42seoul.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:52:04 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/07 17:06:54 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **cmd)
{
	char	*pwd;
	char	*buf;

	(void)cmd;
	buf = ft_calloc(4096, 1);
	if (!buf)
		throw_error(MALLOC_ERR);
	pwd = getcwd(buf, 4096);
	if (!pwd)
		throw_error(MALLOC_ERR);
	printf("%s\n", pwd);
	free(buf);
}