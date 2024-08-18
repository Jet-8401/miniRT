/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:31:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/08/16 13:22:44 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int init_mlx_all(t_scene *scene)
{
    t_mlx *mlx;

    mlx = gc_calloc(sizeof(t_mlx));
    if (!mlx)
        return (-1);
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return (ft_err("mlx_init failed", 0), -1);
    if (init_mlx_window(mlx) == -1)
        return (-1);
    mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    if (!mlx->img.img)
        return (ft_err("mlx_new_image failed", 0), -1);
    mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_len, &mlx->img.endian);
    scene->mlx = mlx;
    init_camera(scene);
    init_objects(scene, 'p');
    init_objects(scene, 's');
    init_objects(scene, 'c');
    return (0);
}

int init_mlx_window(t_mlx *mlx)
{
    mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
    if (!mlx->win)
    {
        destroy_mlx(mlx);
        return (ft_err("mlx_new_window failed", 0), -1);
    }
    return (0);
}

void destroy_mlx(t_mlx *mlx)
{
    if (mlx->img.img)
        mlx_destroy_image(mlx->mlx, mlx->img.img);
    if (mlx->win)
        mlx_destroy_window(mlx->mlx, mlx->win);
    if (mlx->mlx)
        mlx_destroy_display(mlx->mlx);
    gc_free(mlx);
}

void init_objects(t_scene *scene, char type)
{
    t_obj *obj;

    obj = gc_calloc(sizeof(t_obj));
    if (!obj)
        return ;
    obj->type = type;
    if (type == 'p')
        add_plane_obj(scene, obj);
    else if (type == 's')
        add_sphere_obj(scene, obj);
    else if (type == 'c')
        add_cylinder_obj(scene, obj);
    obj->next = scene->obj;
    scene->obj = obj;
}

void add_plane_obj(t_scene *scene, t_obj *object)
{
    object->pos = scene->plane->pos;
    object->dir = scene->plane->dir;
    object->color = scene->plane->color;
    object->diameter = 0;
    object->height = 0;
    object->object.plane = *scene->plane;
}

void add_sphere_obj(t_scene *scene, t_obj *object)
{
    object->pos = scene->sphere->pos;
    object->dir = (t_vec3){0, 0, 0};
    object->color = scene->sphere->color;
    object->diameter = scene->sphere->diameter;
    object->height = 0;
    object->object.sphere = *scene->sphere;
}

void add_cylinder_obj(t_scene *scene, t_obj *object)
{
    object->pos = scene->cylinder->pos;
    object->dir = scene->cylinder->dir;
    object->color = scene->cylinder->color;
    object->diameter = scene->cylinder->diameter;
    object->height = scene->cylinder->height;
    object->object.cylinder = *scene->cylinder;
}
