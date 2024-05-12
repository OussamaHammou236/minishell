/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockention.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:34:34 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/10 14:51:20 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ls -la > ls | pwd > out | diff out ls | echo $? | echo $PATH

void tockention(char *str,t_data *data)
{
	int i;
	i = 0;
	data->i = 0;
	data->cmd = ft_mini_split(str,' ');
	while(data->cmd[i])
	{
		data->j = 0;
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

void check_tocken(char *str)
{
	t_data data;
	data.len = cont_words(str,' ');
	data.tab = malloc(data.len);
	tockention(str,&data);
	data.i = 0;
	while(data.i < data.len)
	{
		printf("%d\n",data.tab[data.i]);
		data.i++;
	}
}