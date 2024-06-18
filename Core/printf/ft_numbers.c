/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:10:19 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/18 21:15:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putnbr(long n)
{
	char	output[20];

	if (n < 0)
	{
		write (1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	*output = (n % 10) + '0';
	write(1, &output, 1);
}

void	ft_putnbrUI(unsigned int n)
{
    char	output[20];

	if (n >= 10)
		ft_putnbr(n / 10);
	*output = (n % 10) + '0';
	write(1, &output, 1);
}