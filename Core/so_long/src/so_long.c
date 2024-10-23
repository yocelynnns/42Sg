/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:30:22 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/23 20:06:41 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_filename(char *filename)
{
    int len;
    
    len = ft_strlen(filename);
    if (len < 4)
        return (1);
    return (ft_strcmp(&filename[len - 4], ".ber") == 0);
}

int read_map(t_struct *m_struct, char **argv)
{
    char    buf[BUFFER_SIZE];
    int     bytes_read;

    m_struct->map_fd = open(argv[1], O_RDONLY);
    if (m_struct->map_fd == -1)
        return (perror("Error: Could not open .ber file"), 0);
    bytes_read = read(m_struct->map_fd, buf, BUFFER_SIZE);
    if (bytes_read == -1)
        return (perror("Error: Failed to read map"), close(m_struct->map_fd), 0);
    else if (bytes_read == 0)
        return (printf("Error: Map is empty\n"), close(m_struct->map_fd), 0);
    else if (bytes_read > 560)
        return (printf("Error: Map too big\n"), close(m_struct->map_fd), 0);
    buf[bytes_read] = '\0';
    m_struct->map = ft_split(buf, '\n');
    m_struct->map_cp = ft_split(buf, '\n');
    if (!m_struct->map || !m_struct->map_cp)
        return (perror("Error: Failed to split map"), close(m_struct->map_fd), 0);
    close(m_struct->map_fd);
    return (1);
}

void    init_map(t_struct *m_structs, t_temp *temp)
{
    m_structs->map = NULL;
    m_structs->map_cp = NULL;
    m_structs->map_fd = 0;
    m_structs->map_w = 0;
    m_structs->map_h = 0;
    m_structs->collect = 0;
    m_structs->player = 0;
    m_structs->exit = 0;
    m_structs->player_x = -1;
    m_structs->player_y = -1;
    temp->c = 0;
    temp->e = 0;
} 

void map_check(char **argv, t_struct *m_structs, t_temp *temp)
{
    if (!read_map(m_structs, argv))
        ft_error("", m_structs);
    map_dimension(m_structs);
    if (!rect_check(m_structs))
        ft_error("Error: Map is not a rectangle.\n", m_structs);
    if (!wall_check(m_structs))
        ft_error("Error: Map is not surrounded by walls.\n", m_structs);
    if (!valid_elem(m_structs))
        ft_error("Error: Invalid elements in the map.\n", m_structs);
    count_elems(m_structs);
    check_elem(m_structs);
    startfill(m_structs);
    if (!map_valid(temp))
        ft_error("Error: Not all collectibles and exits have been reached.\n", m_structs);
}

int main(int argc, char **argv)
{
    t_struct m_structs;
    t_temp temp;
    t_game game;

    if (argc != 2)
        return (fprintf(stderr, "Error!\nUsage: ./so_long <map_file.ber>\n"), 1);
    if (!check_filename(argv[1]))
        return (fprintf(stderr, "Error: Invalid file format. Expected a .ber file.\n"), 1);
    init_map(&m_structs, &temp);
    map_check(argv, &m_structs, &temp);
    
    if(init_game(&m_structs, &game) == 1)
        exit(1);
    load_images(&game);
    render_map(&game, &m_structs);
    handle_events(&game);
    cleanup_game(&game);
    // mlx_key_hook();
    // mlx_hook();
    // mlx_loop();

    ft_error("Perfect!\n", &m_structs);
    return (0);
}


// void free_all(t_struct *m_structs)
// {
//     int i = 0;
//     if (!m_structs->map)
//         return;
//     while (m_structs->map[i])
//     {
//         free(m_structs->map[i]);
//         i++;
//     }
//     free(m_structs->map);
// }

    // int i = 0;
    // while (m_structs.map[i])
    // {
    //     printf("%s\n", m_structs.map[i]);
    //     i++;
    // }
    // printf("-----------------------------\n");
    // i = 0;
    // while (m_structs.map_cp[i])
    // {
    //     printf("%s\n", m_structs.map_cp[i]);
    //     i++;
    // }