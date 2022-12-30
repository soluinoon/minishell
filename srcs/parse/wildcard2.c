/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <jihonkim@42student.42seoul.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:52:27 by jihonkim          #+#    #+#             */
/*   Updated: 2022/12/30 11:53:11 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_tok_cmd(t_token *tok, int i)
{
	int		j;
	char	*ret;

	j = 0;
	while (tok->line[i + j] != 0 && tok->line[i + j] != ' ')
		j++;
	ret = (char *)malloc(sizeof(char) * j + 1);
	ret[j--] = 0;
	while (j >= 0)
	{
		ret[j] = tok->line[i + j];
		j--;
	}
	return (ret);
}

char	*get_tok_cmd(t_token *tok, int idx)
{
	int		i;
	char	*ret;

	i = 0;
	while (tok->line[i] && idx != 0)
	{
		if (tok->line[i] == '\"' || tok->line[i] == '\'')
		{
			i++;
			while (tok->line[i] != '\"' && tok->line[i] != '\'')
				i++;
		}
		if (tok->line[i] == ' ')
			idx--;
		i++;
	}
	ret = set_tok_cmd(tok, i);
	return (ret);
}

int	com_wild(t_token *tok, int idx, char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_tok_cmd(tok, idx);
	if (ft_strchr(tmp, '*') == 0)
		return (free_wild(tmp, 0));
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			i++;
			while (tmp[i] != '\"' && tmp[i] != '\'')
				i++;
		}
		if (tmp[i] == '*')
			return (free_wild(tmp, 1));
		i++;
	}
	return (free_wild(tmp, 0));
}
