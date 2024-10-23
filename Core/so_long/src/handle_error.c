/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:47:42 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/23 17:13:50 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_2d(char **memory)
{
	size_t	i;

	i = 0;
	while (memory[i])
	{
		free(memory[i]);
		i++;
	}
	free(memory);
	memory = NULL;
}

void	clean_struct(t_struct *m_struct)
{
	if (m_struct->map)
		free_2d(m_struct->map);
	if (m_struct->map_cp)
		free_2d(m_struct->map_cp);
	if (m_struct->map_fd != -1)
		close(m_struct->map_fd);
}

void	ft_error(char *s, t_struct *l_struct)
{
	clean_struct(l_struct);
	printf("%s", s);
	exit(1);
}
