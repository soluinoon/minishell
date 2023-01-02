/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:50:40 by kko               #+#    #+#             */
/*   Updated: 2023/01/02 09:50:41 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	start_open(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tok->parent->err_flag_redir == -1)
			break ;
		if (tok->err_flag_redir == 2)
			break ;
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