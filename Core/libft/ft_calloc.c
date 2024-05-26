/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:19:28 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/24 14:35:01 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, nmemb);
	return (ptr);
}

/* int main(void)
{
    int* p1 = ft_calloc(2, sizeof(int));    
    int* p2 = ft_calloc(1, sizeof(int[4]));
    int* p3 = ft_calloc(4, sizeof *p3);     
 
    if (p2)
    {
        for (int n = 0; n < 4; ++n) // print the array
            printf("p2[%d] == %d\n", n, p2[n]);
    }
 
    free(p1);
    free(p2);
    free(p3);
} */

/* int main() {
    size_t nmemb = 5;
    size_t size = sizeof(int);
    int *arr = (int *)ft_calloc(nmemb, size);

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    size_t i = 0;
    while (i < nmemb) {
        printf("arr[%zu] = %d\n", i, arr[i]);
        i++;
    }

    free(arr);

    return 0;
}   */
