/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:27:42 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/07/22 19:49:28 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strcpy(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return(s1);
}

#include <stdio.h>
//#include <string.h>
int main()
{
	char s1[] = "helloworld";
	char s2[] = "12";

	ft_strcpy(s1, s2);
	//strcpy(s1, s2);
	printf("%s", s2);
	return (0);
}       
