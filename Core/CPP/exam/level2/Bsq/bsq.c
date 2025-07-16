/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:37:24 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/16 14:52:45 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int get_line_len(const char *line)
{
    int len = 0;
    while (line[len] && line[len] != '\n')
        len++;
    return len;
}

int load_map(Bsq *bsq, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Failed to open.\n");
        return 0;
    }
    
    bsq->cols = 0;
    bsq->rows = 0;
    
    size_t len = 0;
    char *line = NULL;

    while (getline(&line, &len, file) != -1)
    {
        if (bsq->cols == 0)
            bsq->cols = get_line_len(line);
        bsq->rows++;
    }
    rewind(file);
    
    bsq->map = (char **)malloc(sizeof(char *) * bsq->rows);
    bsq->dp = (int **)malloc(sizeof(int *) * bsq->rows);
    
    int row = 0;
    while (getline(&line, &len, file) != -1 && row < bsq->rows)
    {
           
    }
}

void solve_map(Bsq *bsq)
{
   int maxSize = 0;
   int maxRow = 0;
   int maxCol = 0;
   
   int i = 0;
   while (i < bsq->rows)
   {
        int j = 0;
        while (j < bsq->cols)
        {
            if (bsq->map[i][j] == '.')
            {
                if (i == 0 || j == 0)
                    bsq->dp[i][j] = 1;
                else
                {
                    int top = bsq->dp[i - 1][j];
                    int left = bsq->dp[i][j - 1];
                    int topleft = bsq->dp[i - 1][j - 1];
                    int min;
                    if (top < left)
                        min = top;
                    else
                        min = left;
                    if (topleft < min)
                        min = topleft;
                    bsq->dp[i][j] = min + 1;
                }
                if (bsq->dp[i][j] > maxSize)
                {
                    maxSize = bsq->dp[i][j];
                    maxRow = i;
                    maxCol = j;
                }
            } else
                bsq->dp[i][j] = 0;
            j++;
        }
        i++;
   }

    i = maxRow - maxSize + 1;
    while (i <= maxRow)
    {
        int j = maxCol - maxSize + 1;
        while(j <= maxCol)
        {
            bsq->map[i][j] = 'x';
            j++;
        }
        i++;
    }
}

void print_map(Bsq *bsq)
{
    int i = 0;
    while (i < bsq->rows)
    {
        int j = 0;
        while (j < bsq->cols)
        {
            fputc(bsq->map[i][j], stdout);
            j++;
        }
        fputs("\n", stdout);
        i++;
    }
}

void free_map(Bsq *bsq)
{
    int i = 0;
    while (i < bsq->rows)
    {
        free(bsq->map[i]);
        free(bsq->dp[i]);
        i++;
    }
    free(bsq->map);
    free(bsq->dp);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage is wrong!\n");
        return 1;
    }

    Bsq bsq;
    if (!load_map(&bsq, argv[1]))
        return 1;
    solve_map(&bsq);
    print_map(&bsq);
    free_map(&bsq);
    return 0;
}

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
//         return 1;
//     }

//     Bsq bsq;
//     if (!load_map(&bsq, argv[1]))
//         return 1;

//     solve_map(&bsq);
//     print_map(&bsq);
//     free_map(&bsq);
//     return 0;
// }

// int load_map(Bsq *bsq, const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (!file)
//     {
//         fprintf(stderr, "Failed to open file.\n");
//         return 0;
//     }

//     bsq->rows = 0;
//     bsq->cols = 0;

//     size_t len = 0;
//     char *line = NULL;

//     while (getline(&line, &len, file) != -1)
//     {
//         if (bsq->cols == 0)
//             bsq->cols = get_line_length(line);
//         bsq->rows++;
//     }

//     rewind(file);

//     bsq->map = (char **)malloc(sizeof(char *) * bsq->rows);
//     bsq->dp = (int **)malloc(sizeof(int *) * bsq->rows);

//     int row = 0;
//     while (getline(&line, &len, file) != -1 && row < bsq->rows)
//     {
//         bsq->map[row] = (char *)malloc(sizeof(char) * (bsq->cols + 1));
//         bsq->dp[row] = (int *)calloc(bsq->cols, sizeof(int));

//         int i = 0;
//         while (i < bsq->cols)
//         {
//             if (line[i] && line[i] != '\n')
//                 bsq->map[row][i] = line[i];
//             else
//                 bsq->map[row][i] = '\0';
//             i++;
//         }
//         bsq->map[row][bsq->cols] = '\0';
//         row++;
//     }

//     free(line);
//     fclose(file);
//     return 1;
// }

// void solve_map(Bsq *bsq)
// {
//     int maxSize = 0;
//     int maxRow = 0;
//     int maxCol = 0;

//     int i = 0;
//     while (i < bsq->rows)
//     {
//         int j = 0;
//         while (j < bsq->cols)
//         {
//             if (bsq->map[i][j] == '.')
//             {
//                 if (i == 0 || j == 0)
//                     bsq->dp[i][j] = 1;
//                 else
//                 {
//                     int top = bsq->dp[i - 1][j];
//                     int left = bsq->dp[i][j - 1];
//                     int topleft = bsq->dp[i - 1][j - 1];
//                     int min;
//                     if (top < left)
//                         min = top;
//                     else
//                         min = left;
//                     if (topleft < min)
//                         min = topleft;
//                     bsq->dp[i][j] = min + 1;
//                 }

//                 if (bsq->dp[i][j] > maxSize)
//                 {
//                     maxSize = bsq->dp[i][j];
//                     maxRow = i;
//                     maxCol = j;
//                 }
//             } else {
//                 bsq->dp[i][j] = 0;
//             }
//             j++;
//         }
//         i++;
//     }

//     i = maxRow - maxSize + 1;
//     while (i <= maxRow)
//     {
//         int j = maxCol - maxSize + 1;
//         while (j <= maxCol)
//         {
//             bsq->map[i][j] = 'x';
//             j++;
//         }
//         i++;
//     }
// }

// void print_map(Bsq *bsq)
// {
//     int i = 0;
//     while (i < bsq->rows)
//     {
//         int j = 0;
//         while (j < bsq->cols)
//         {
//             fputc(bsq->map[i][j], stdout);
//             j++;
//         }
//         fputs("\n", stdout);
//         i++;
//     }
// }