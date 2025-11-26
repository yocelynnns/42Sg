/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:57:29 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/07/22 22:12:03 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
int main(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 2)
	{
		if ((argv[1][i] >= 'a' && argv[1][i] <= 'm') || \
				(argv[1][i] >= 'A' && argv[1][i] <= 'M'))
			argv[1][i] = (argv[1][i] + 13);
		else if ((argv[1][i] >= 'n' && argv[1][i] <= 'z') || \
			(argv[1][i] >= 'N' && argv[1][i] <= 'Z'))
                        argv[1][i] = (argv[1][i] - 13);
		write (1, &argv[1][i], 1);
		i++;
	}
}
