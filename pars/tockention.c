/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockention.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:34:34 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/21 15:57:40 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ls -la > ls | pwd > out | diff out ls | echo $? | echo $PATH

void  tockention(char *str,t_data *data)
{
	int i;
	i = 0;
	data->i = 0;
	data->cmd = ft_mini_split(str,' ');
	while(data->cmd[i] && data->i < data->len)
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
		data->i++;
		i++;
	}
}

int check(t_data *data)
{
	data->i = 0;
	if(data->tab[0] == PIP || data->tab[data->len - 1] !=  WORD)
		return -1;
	while(data->i < data->len)
	{
		if (data->tab[data->i] != WORD && data->tab[data->i] != PIP&& data->tab[data->i + 1] != WORD)
			return -1;
		data->i++;
	}
	return 0;
}

int check_tocken(char *str,t_input **list,int flag)
{
	t_data data;
	data.len = cont_words(str,' ');
	data.tab = (int *)malloc(data.len * sizeof(int));
	tockention(str,&data);
	if(flag)
		(*list)->type = data.tab;
	if(check(&data) == -1)
		return -1;
	return 0;
}
