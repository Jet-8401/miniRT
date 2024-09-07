/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/01 23:37:35 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void init_camera(t_scene *scene)
{
    t_screen *screen;
    double new_fov;

    screen = gc_calloc(sizeof(t_screen));
    screen->screen_width = WIDTH;
    screen->screen_height = HEIGHT;
    new_fov = scene->cam->fov / 2.0;
    screen->scale = tan((new_fov * 3.1415926535f) / 180.0f);
    screen->aspect_ratio = screen->scale / (16.0 / 9.0);
    screen->right = normalize(merge_vect(scene->cam->dir, (t_vec3){0.0, 1.0, 0.0}));
    screen->up = normalize(merge_vect(scene->cam->dir, screen->right));
    screen->right = normalize(merge_vect(scene->cam->dir, screen->up));
    scene->screen = screen;
}

int render_scene(t_scene *scene)
{
    t_render render;

    ft_memset(&render, 0, sizeof(t_render));
    pixel_draw(scene, &render);
    mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
    fps_display(scene->mlx);
    render_time_display(scene->mlx);
    return (0);
}

void pixel_draw(t_scene *scene, t_render *render)
{
    size_t x;
    size_t y;

    y = 0;
    init_camera(scene);
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            new_init_camera(scene, &render->prime_ray, (float)x, (float)y);
            render->color_ambiant = color_rgb(ambiant_color(render, scene));
            new_mlx_pixel_put(scene->mlx, x, y, render->color_ambiant);
            x++;
        }
        y++;
    }
}

void new_init_camera(t_scene *scene, t_ray_view *prime_ray, float x, float y)
{
    t_scene *tmp_scene;
    t_vec3 coord;
    t_vec3 vertical;
    t_vec3 horizontal;
    t_vec3 res;

    tmp_scene = scene;
    prime_ray->origin = new_vector(tmp_scene->cam->pos.x, tmp_scene->cam->pos.y, tmp_scene->cam->pos.z);
    coord.x = ((2.0f * x) / WIDTH) - 1;
    coord.y = ((2.0f * y) / HEIGHT) - 1;
    coord.z = 0;
    vertical = mult_vec3(tmp_scene->screen->up, coord.y * tmp_scene->screen->aspect_ratio);
    horizontal = mult_vec3(tmp_scene->screen->right, coord.x * tmp_scene->screen->scale);
    res = add_vec3(vertical, horizontal);
    res = add_vec3(res, scene->cam->dir);
    res = add_vec3(res, scene->cam->pos);
    prime_ray->direction = sub_vec3(res, prime_ray->origin);
    normalize_bis(&prime_ray->direction);
}
