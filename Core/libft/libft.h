/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:10:33 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/05/27 02:22:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

int atoi(const char *nptr);
void ft_bzero(void *s, size_t n);
void *ft_calloc(size_t nmemb, size_t size);
int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isascii(int c);
int ft_isdigit(int c);
int ft_isprint(int c);
void *ft_memchr(const void *str, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);
void *ft_memset(void *s, int c, size_t n);
char **ft_split(char const *s, char c);
char *ft_strchr(const char *s, int c);
char *ft_strdup(const char *s);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcat(char *dst, const char *src, size_t size);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
size_t ft_strlen(const char *s);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *strnstr(const char *big, const char *little, size_t len);
char *ft_strrchr(char *str, int chr);
char *ft_strtrim(char const *s1, char const *set);
char *ft_substr(char const *s, unsigned int start, size_t len);
int ft_tolower(int c);
int ft_toupper(int c);
void ft_putchar_fd(char c, int fd);

#endif