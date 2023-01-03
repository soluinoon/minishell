/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:20:38 by kko               #+#    #+#             */
/*   Updated: 2023/01/03 10:05:39 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_out(t_token *tok, t_token *tmp)
{
	if (tmp->type == TOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 1), \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 1));
			tok->fd_out = -1;
			tok->parent->err_flag_redir = -1;
		}
	}
	else if (tmp->type == TADDOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 2), \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 2));
			tok->fd_out = -1;
			tok->parent->err_flag_redir = -1;
		}
	}
}

static void	open_in(t_token *tok, t_token *tmp)
{
	if (tmp->type == TIN)
	{
		tok->fd_in = open(find_redir(tmp->line + 1), O_RDONLY);
		if (tok->fd_in < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 1));
			tok->fd_in = -1;
			tok->parent->err_flag_redir = -1;
		}
	}
	else if (tmp->type == TDOC)
	{
		set_signal(FORK);
		signal(SIGQUIT, SIG_IGN);
		tok->fd_in = here_doc(find_redir(tmp->line + 2), tok);
		set_signal(BASH);
	}
}

static void	start_open(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tok->parent->err_flag_redir == -1)
			break ;
		if (tmp->err_flag_redir == 2)
		{
			tok->parent->err_flag_redir = -1;
			break ;
		}
		else if (tmp->type == TOUT || tmp->type == TADDOUT)
		{
			if (tok->fd_out != -1)
				close_util(tok->fd_out, tok);
			open_out(tok, tmp);
		}
		else if (tmp->type == TIN || tmp->type == TDOC)
		{
			if (tok->fd_in != -1)
				close_util(tok->fd_in, tok);
			open_in(tok, tmp);
		}
		tmp = tmp->next;
	}
}

int	get_index_redir(char *tmp, int i)
{
	while (tmp[i] != 0 && tmp[i] != ' ')
	{
		if (ft_is_comma(tmp[i]))
			push_index_com(tmp, &i);
		i++;
	}
	return (i);
}

char	*get_prev_line(t_token *tok, t_token *first, int idx)
{
	char	*tmp;
	char	*ret;
	int		i;

	(void)tok;
	tmp = first->parent->right->line;
	i = 0;
	while (tmp[i] && idx != 0)
	{
		if (ft_is_redir(tmp[i]))
		{
			i++;
			if (ft_is_redir(tmp[i]))
				i++;
			idx--;
		}
		i++;
	}
	while (ft_is_redir(tmp[i]) == NO_DIREC)
		i++;
	ret = ft_substr(tmp, i, get_index_redir(tmp, i));
	return (ret);
}

int	com_wild_redir(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_is_comma(tmp[i]))
		{
			push_index_com(tmp, &i);
		}
		else if (tmp[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_redir(char *s)
{
	if (ft_is_redir(*s))
		s++;
	if (ft_is_redir(*s))
		s++;
	while (*s == ' ')
		s++;
	return (s);
}

void	change_lien(t_token *tok, char **tmp1)
{
	char	*tmp;

	tmp = tok->line;
	tok->line = ft_strdup(tmp1[0]);
	free(tmp);
	tmp = tok->line;
	if (tok->type == TDOC)
		tok->line = ft_strjoin("<<", tok->line);
	if (tok->type == TIN)
		tok->line = ft_strjoin("<", tok->line);
	if (tok->type == TOUT)
		tok->line = ft_strjoin(">", tok->line);
	if (tok->type == TADDOUT)
		tok->line = ft_strjoin(">>", tok->line);
	free(tmp);
}

void	edit_wild_redir(t_token *tok, t_token *first, int idx)
{
	char	*tmp;
	char	**tmp1;

	tmp = get_prev_line(tok, first, idx);
	if (com_wild_redir(tmp) == 0)
	{
		free(tmp);
		return ;
	}
	free(tmp);
	if (cnt_cwd_wild(tok, ft_redir(tok->line)) != 1)
	{
		tok->err_flag_redir = 2;
		throw_error_message(NULL, "*", "ambiguous redirect", 0);
		return ;
	}
	tmp1 = make_arrs_with_wild(tok, ft_redir(tok->line));
	change_lien(tok, tmp1);
	free_cmd(tmp1);
}

void	expansion_wild_redir(t_token *tok, t_token *first)
{
	int		i;
	int		j;

	j = 0;
	while (tok)
	{
		i = 0;
		while (tok->line[i])
		{
			if (tok->line[i] == '*')
			{
				edit_wild_redir(tok, first, j);
				break ;
			}
			i++;
		}
		if (tok->err_flag_redir == 2)
			return ;
		tok = tok->next;
		j++;
	}
}

void	open_redir(t_token *tok)
{
	if (tok == 0)
		return ;
	open_redir(tok->left);
	open_redir(tok->right);
	if ((tok->type == TOUT || tok->type == TADDOUT || \
	tok->type == TIN || tok->type == TDOC) && g_errno != -2)
	{
		if (tok->type != TDOC)
			expansion_wild_redir(tok, tok);
		start_open(tok);
	}
}
