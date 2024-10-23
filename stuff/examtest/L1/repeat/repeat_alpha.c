/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:59:26 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/08/06 19:33:15 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;
	int count = 0;
	
	if (argc == 2)
	{
		while (argv[1][i])
		{
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
				count = argv[1][i] - 'a' + 1;
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
				count = argv[1][i] - 'A' + 1;
			else
				count = 1;
			while (count--)
				write (1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
}
