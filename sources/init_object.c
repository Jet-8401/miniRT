/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:10:23 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/01 23:46:33 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void init_objects_all(t_scene *scene)
{
    int i;
    
    scene->obj = NULL;
    i = 1;
    add_plane_obj(scene->plane, 'p', &scene->obj, &i);
    add_sphere_obj(scene->sphere, 's', &scene->obj, &i);
    add_cylinder_obj(scene->cylinder, 'c', &scene->obj, &i);
}

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