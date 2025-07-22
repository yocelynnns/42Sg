/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:00:47 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/30 13:40:10 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n > 0)
	{
		*temp = 0;
		temp++;
		n--;
	}
	s = temp;
}

/*int main() {
    char buffer[10];

    // Fill buffer with alphabet characters for testing
    for (int i = 0; i < 10; i++) {
        buffer[i] = 'A' + i;
    }

    // Print buffer before bzero
    printf("Buffer before bzero: ");
    for (int i = 0; i < 10; i++) {
        printf("%c ", buffer[i]);
    }
    printf("\n");

    // Apply bzero to the buffer
    ft_bzero(buffer, 5);

    // Print buffer after bzero
    printf("Buffer after bzero: ");
    for (int i = 0; i < 10; i++) {
        if (buffer[i] == 0)
            printf("0 ");  // Print zeroed bytes as '\0' for clarity
        else
            printf("%c ", buffer[i]);
    }
    printf("\n");

    return 0;
}*/
