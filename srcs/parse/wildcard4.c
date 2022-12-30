/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:52:19 by jihonkim          #+#    #+#             */
/*   Updated: 2022/12/30 17:21:52 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	other_filling(t_token *tok, int *idx, char ***new, int j)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = *new;
	while (tok->cmd[i + *idx])
	{
		tmp[j] = ft_strdup(tok->cmd[i + *idx]);
		i++;
	}
}

char	**filling_cmd(t_token *tok, int *idx, char **tmp, int cnt)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (cnt + 1));
	new[cnt] = 0;
	while (new[i] && i < *idx)
	{
		new[i] = ft_strdup(tok->cmd[i]);
		i++;
	}
	while (tmp[j])
	{
		new[i] = ft_strdup(tmp[j]); // i = 1 j = 0
		j++;
		i++;
	}
	*idx = i - 1;
	other_filling(tok, idx, &new, i);
	return (new);
}

int	search_edit_wild(t_token *tok, int *i)
{
	char	**new;
	char	**tmp;
	char	**tmp_cmd;
	int		cnt;

	cnt = 0;
	cnt += cnt_cwd_wild(tok, tok->cmd[*i]);
	if (cnt == 0)
	{
		return (0);
	}
	cnt += cnt_cmd(tok->cmd);
	tmp = make_arrs_with_wild(tok, tok->cmd[*i]);
	new = filling_cmd(tok, i, tmp, cnt);
	int	z = 0;
	tmp_cmd = tok->cmd;
	tok->cmd = new;
	free_cmd(tmp_cmd);
	free_cmd(tmp);
	return (0);
}

int	wild_type(t_token *tok, int *i)
{
	if (check_wild(tok->cmd[*i]) != 0)
	{
		if (edit_wild(tok, 0, i) < 0)
			return (-1);
	}
	else
	{
		if (search_edit_wild(tok, i) < 0)
			return (-1);
	}
	return (0);
}

int	expansion_wild(t_token *tok)
{
	int	i;

	while (tok)
	{
		i = 0;
		if (tok->type == TCMD)
		{
			while (tok->cmd[i])
			{
				if (com_wild(tok, i, tok->cmd[i]) == 1)
				{
					if (wild_type(tok, &i) < 0)
						return (-1);
				}
				i++;
			}
		}
		tok = tok->next;
	}
	return (0);
}