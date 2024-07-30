/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockention.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:34:34 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/28 12:33:32 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	tockention(char *str, t_data *data, t_trash **trash)
{
	int	i;

	i = 0;
	data->i = 0;
	data->cmd = ft_mini_split(str, ' ', trash);
	while (data->cmd[i] && data->i < data->len)
	{
		if (data->cmd[i][0] == '|')
			data->tab[data->i] = PIP;
		else if (data->cmd[i][0] == '>' && data->cmd[i][1] == '>')
			data->tab[data->i] = RE_INF;
		else if (data->cmd[i][0] == '<' && data->cmd[i][1] == '<')
			data->tab[data->i] = RE_OUTF;
		else if (data->cmd[i][0] == '>')
			data->tab[data->i] = IN_F;
		else if (data->cmd[i][0] == '<')
			data->tab[data->i] = OUT_F;
		else
			data->tab[data->i] = WORD;
		if (data->tab[data->i] != WORD && data->tab[data->i] != PIP)
			data->j++;
		check_herdoc(data, trash);
		data->i++;
		i++;
	}
}

int	check(t_data *data)
{
	data->i = 0;
	if (data->tab[0] == PIP || data->tab[data->len - 1] == PIP)
		return (printf("minishell : syntax error near unexpected token `|'\n"),
			-1);
	while (data->i < data->len)
	{
		if (data->tab[data->i] != WORD && data->tab[data->i] != PIP && data->i
			+ 1 == data->len)
		{
			printf("minishell : syntax error near ");
			printf("unexpected token `newline'\n");
			return (-1);
		}
		else if ((data->tab[data->i] != WORD && data->tab[data->i] != PIP
				&& data->tab[data->i + 1] != WORD)
			|| (data->tab[data->i] == PIP && data->tab[data->i + 1] == PIP))
		{
			printf("minishell : syntax error near unexpected token '%s'\n",
				data->cmd[data->i + 1]);
			return (-1);
		}
		data->i++;
	}
	return (0);
}

int	malloc_of_node(t_input **list, t_trash **trash, t_data *data)
{
	(*list)->type = data->tab;
	(*list)->red = malloc(((data->j * 2) + 1) * sizeof(char *));
	(*list)->cmd = malloc((data->i - (data->j * 2) + 1) * sizeof(char *));
	(*list)->is_qouts = malloc((data->j) * sizeof(int));
	(*list)->len = data->j;
	add_to_trash((*list)->is_qouts, trash);
	add_to_trash((*list)->red, trash);
	add_to_trash((*list)->cmd, trash);
	if (!(*list)->red || !(*list)->cmd || !(*list)->is_qouts)
		return (-1);
	(*list)->cmd[data->i - (data->j * 2)] = NULL;
	(*list)->red[(data->j * 2)] = NULL;
	return (0);
}

int	check_tocken(char *str, t_input **list, int flag, t_trash **trash)
{
	t_data	data;

	data.len = cont_words(str, ' ');
	data.nb_of_herdoc = 0;
	if (data.len == 0)
		return (1);
	data.tab = (int *)malloc(data.len * sizeof(int));
	add_to_trash(data.tab, trash);
	data.j = 0;
	tockention(str, &data, trash);
	if (flag)
	{
		if (malloc_of_node(list, trash, &data) == -1)
			return (-1);
	}
	if (check(&data) == -1 && !flag)
		return (-1);
	return (0);
}
