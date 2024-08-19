/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:31:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/08/19 13:51:06 by akinzeli         ###   ########.fr       */
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
    init_objects_all(scene);
    //init_objects(scene, 'p');
    //init_objects(scene, 's');
    //init_objects(scene, 'c');
    print_all_objects(scene->obj);
    return (0);
}

void init_objects_all(t_scene *scene)
{
    t_obj *obj;

    obj = gc_calloc(sizeof(t_obj));
    if (!obj)
        return ;
    add_plane_obj(scene, 'p', obj);
    add_sphere_obj(scene, 's', obj);
    add_cylinder_obj(scene, 'c', obj);
    scene->obj = obj;
}

void print_all_objects(t_obj *obj)
{
    while (obj)
    {
        printf("type: %c\n", obj->type);
        printf("pos: %f %f %f\n", obj->pos.x, obj->pos.y, obj->pos.z);
        printf("dir: %f %f %f\n", obj->dir.x, obj->dir.y, obj->dir.z);
        printf("color: %d %d %d\n", obj->color.r, obj->color.g, obj->color.b);
        printf("diameter: %f\n", obj->diameter);
        printf("height: %f\n", obj->height);
        obj = obj->next;
    }
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
    if (type == 'p')
        add_plane_obj(scene, 'p', obj);
    else if (type == 's')
        add_sphere_obj(scene, 's', obj);
    else if (type == 'c')
        add_cylinder_obj(scene, 'c', obj);
    scene->obj = obj;
}

void add_plane_obj(t_scene *scene, char type, t_obj *object)
{
    while (scene->plane->next)
    {
        object->pos = scene->plane->pos;
        object->dir = scene->plane->dir;
        object->color = scene->plane->color;
        object->diameter = 0;
        object->height = 0;
        object->type = type;
        object->object.plane = *scene->plane;
        object->next = scene->obj;
        scene->plane = scene->plane->next;
    }
}

void add_sphere_obj(t_scene *scene, char type, t_obj *object)
{
    while (scene->sphere->next)
    {
        object->pos = scene->sphere->pos;
        object->dir = (t_vec3){0, 0, 0};
        object->color = scene->sphere->color;
        object->diameter = scene->sphere->diameter;
        object->height = 0;
        object->type = type;
        object->object.sphere = *scene->sphere;
        object->next = scene->obj;
        scene->sphere = scene->sphere->next;
    }
}

void add_cylinder_obj(t_scene *scene, char type, t_obj *object)
{
    while (scene->cylinder->next)
    {
        object->pos = scene->cylinder->pos;
        object->dir = scene->cylinder->dir;
        object->color = scene->cylinder->color;
        object->diameter = scene->cylinder->diameter;
        object->height = scene->cylinder->height;
        object->type = type;
        object->object.cylinder = *scene->cylinder;
        object->next = scene->obj;
        scene->cylinder = scene->cylinder->next;
    }
}
