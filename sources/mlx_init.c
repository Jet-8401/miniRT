/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:31:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/08/25 15:13:36 by akinzeli         ###   ########.fr       */
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
    //fps_counter_init(mlx->fps_counter, FPS_SNAPSHOT_SAMPLES);
    return (0);
}

void init_objects_all(t_scene *scene)
{
    int i;
    scene->obj = NULL;
    i = 0;
    add_plane_obj(scene->plane, 'p', &scene->obj, &i);
    printf("i: %d\n", i);
    add_sphere_obj(scene->sphere, 's', &scene->obj, &i);
    printf("i: %d\n", i);
    add_cylinder_obj(scene->cylinder, 'c', &scene->obj, &i);
    printf("i: %d\n", i);
}


void print_all_objects(t_obj *obj)
{
    while (obj)
    {
        printf("id: %d\n", obj->id);
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

/*void init_objects(t_scene *scene, char type)
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
}*/

void add_plane_obj(t_plane *plane, char type, t_obj **object, int *i)
{
     t_obj *tmp;

    while (plane)
    {
        tmp = gc_calloc(sizeof(t_obj));
        if (!tmp)
            return ;
        tmp->id = *i;
        tmp->pos = plane->pos;
        tmp->dir = plane->dir;
        tmp->color = plane->color;
        tmp->diameter = 0;
        tmp->height = 0;
        tmp->type = type;
        tmp->object.plane = *plane;
        tmp->next = *object;
        *object = tmp;
        (*i)++;
        plane = plane->next;
    }
}

void add_sphere_obj(t_sphere *sphere, char type, t_obj **object, int *i)
{
    t_obj *tmp;

    while (sphere)
    {
        tmp = gc_calloc(sizeof(t_obj));
        if (!tmp)
            return ;
        tmp->id = *i;
        tmp->pos = sphere->pos;
        tmp->dir = (t_vec3){0, 0, 0};
        tmp->color = sphere->color;
        tmp->diameter = sphere->diameter;
        tmp->height = 0;
        tmp->type = type;
        tmp->object.sphere = *sphere;
        tmp->next = *object;
        *object = tmp;
        (*i)++;
        sphere = sphere->next;
    }
}

void add_cylinder_obj(t_cylinder *cylinder, char type, t_obj **object, int *i)
{
    t_obj *tmp;

    while (cylinder)
    {
        tmp = gc_calloc(sizeof(t_obj));
        if (!tmp)
            return ;
        tmp->id = *i;
        tmp->pos = cylinder->pos;
        tmp->dir = cylinder->dir;
        tmp->color = cylinder->color;
        tmp->diameter = cylinder->diameter;
        tmp->height = cylinder->height;
        tmp->type = type;
        tmp->object.cylinder = *cylinder;
        tmp->next = *object;
        *object = tmp;
        (*i)++;
        cylinder = cylinder->next;
    }
}
