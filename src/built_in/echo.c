/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:02:39 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/31 21:02:40 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_option(char *in)
{
	int	i;

	i = 1;
	if (in[0] != '-')
		return (0);
	while (in[i])
	{
		if (in[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	msh_echo(t_list **env, t_list **cmd, int index)
{
	int		i;
	int		nl_flag;
	int		is_behind_options;
	t_cmd	*current_cmd;

	current_cmd = get_content(ft_lstget_element_by_index(*cmd, index));
	nl_flag = 1;
	is_behind_options = 0;
	i = 0;
	while (current_cmd->args[0] && current_cmd->args[++i] && *env)
	{
		if (is_behind_options == 0 && is_valid_option(current_cmd->args[i]))
				nl_flag = 0;
		else
		{
			if (is_behind_options)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(current_cmd->args[i], 1);
			is_behind_options = 1;
		}
	}
	if (nl_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
