/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:48:33 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:19:50 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <string.h>

int load_map(Bsq *bsq, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open file.\n");
        return 0;
    }

    bsq->rows = 0;
    bsq->cols = 0;
    size_t len = 0;
    char *line = NULL;

    // First pass to get rows and cols
    while (getline(&line, &len, fp) != -1) {
        if (bsq->cols == 0) {
            char *newline = strchr(line, '\n');
            if (newline)
                bsq->cols = (int)(newline - line);
            else
                bsq->cols = (int)strlen(line);
        }
        bsq->rows++;
    }

    rewind(fp);

    // Allocate memory
    bsq->map = (char **)malloc(sizeof(char *) * bsq->rows);
    bsq->dp = (int **)malloc(sizeof(int *) * bsq->rows);

    int row = 0;
    while (getline(&line, &len, fp) != -1 && row < bsq->rows)
    {
        bsq->map[row] = (char *)malloc(sizeof(char) * (bsq->cols + 1));
        bsq->dp[row] = (int *)calloc(bsq->cols, sizeof(int));

        strncpy(bsq->map[row], line, bsq->cols);
        bsq->map[row][bsq->cols] = '\0';
        row++;
    }

    free(line);
    fclose(fp);
    return 1;
}

void solve_bsq(Bsq *bsq)
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
                if (i == 0 || j == 0) {
                    bsq->dp[i][j] = 1;
                } else {
                    int top = bsq->dp[i - 1][j];
                    int left = bsq->dp[i][j - 1];
                    int topleft = bsq->dp[i - 1][j - 1];
                    int min;

                    if (top < left) {
                        min = top;
                    } else {
                        min = left;
                    }

                    if (topleft < min) {
                        min = topleft;
                    }

                    bsq->dp[i][j] = 1 + min;
                }
                if (bsq->dp[i][j] > maxSize) {
                    maxSize = bsq->dp[i][j];
                    maxRow = i;
                    maxCol = j;
                }
            } else {
                bsq->dp[i][j] = 0;
            }
            j++;
        }
        i++;
    }
    i = maxRow - maxSize + 1;
    while (i <= maxRow)
    {
        int j = maxCol - maxSize + 1;
        while (j <= maxCol) {
            bsq->map[i][j] = 'x';
            j++;
        }
        i++;
    }
}

void print_map(Bsq *bsq) {
    int i = 0;
    while (i < bsq->rows)
    {
        fputs(bsq->map[i], stdout);
        fputc('\n', stdout);
        i++;
    }
}

void free_bsq(Bsq *bsq)
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
