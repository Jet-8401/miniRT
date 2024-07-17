/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/17 14:08:10 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

void init_camera(t_scene *scene)
{
    scene->screen = gc_calloc(sizeof(t_screen));
    scene->screen->screen_width = WIDTH;
    scene->screen->screen_height = HEIGHT;
    scene->screen->aspect_ratio = (float)WIDTH / (float)HEIGHT;
    scene->screen->scalar_fov = tan((scene->cam.fov * M_PI / 180) / 2);
    scene->screen->camera_direction = scene->cam.dir;
    scene->screen->camera_position = scene->cam.pos;
}

void normalize(t_vec3 *v)
{
    float norm = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= norm;
    v->y /= norm;
    v->z /= norm;
}

void render_scene(t_scene *scene)
{
    t_vec3 ray;
    t_vec3 r;

    ray = ray_direction(scene);
    r.y = 0;
    while (r.y < scene->screen->screen_height)
    {
        r.x = 0;
        while (r.x < scene->screen->screen_width)
        {
            raytrace(scene, ray, &r);
            r.x++;
        }
        r.y++;
    }
    mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
}

t_vec3 ray_direction(t_scene *scene)
{
    t_vec3 ray;

    ray.x = (2 * (scene->screen->screen_width * 0.5) - 1) * scene->screen->aspect_ratio * scene->screen->scalar_fov;
    ray.y = (1 - 2 * (scene->screen->screen_height * 0.5)) * scene->screen->scalar_fov;
    ray.z = -1;
    normalize(&ray);
    return (ray);
}

void raytrace(t_scene *scene, t_vec3 ray, t_vec3 *r)
{
    t_rgb pixel_color;
    t_vec3 intersection;
    t_vec3 normal;
    t_sphere *sphere;
    //t_plane *plane;

    sphere = scene->sphere;
    while (sphere)
    {
        if (intersect_sphere(sphere, scene->screen->camera_position, ray, &intersection, &normal))
        {
            pixel_color = sphere->color;
            break;
        }
        sphere = sphere->next;
    }
    /*plane = scene->plane;
    while (plane)
    {
        if (intersect_plane(plane, scene->screen->camera_position, ray, &intersection, &normal))
        {
            pixel_color = plane->color;
            break;
        }
        plane = plane->next;
    }*/
    if (sphere)
        mlx_pixel_img_put(scene, r->x, r->y, get_color(pixel_color));
        //draw_pixel(scene, r, pixel_color);
}

int get_color(t_rgb color)
{
    return ((color.r << 16) | (color.g << 8) | color.b);
}

void mlx_pixel_img_put(t_scene *scene, int x, int y, int color)
{
    char *dst;

    dst = scene->mlx->img.addr + (y * scene->mlx->img.line_len + x * (scene->mlx->img.bpp / 8));
    *(unsigned int *)dst = color;
}

int intersect_sphere(t_sphere *sphere, t_vec3 camera_position, t_vec3 ray, t_vec3 *intersection, t_vec3 *normal)
{
    t_vec3 oc;
    float a;
    float b;
    float c;
    float discriminant;
    float t;

    oc.x = camera_position.x - sphere->pos.x;
    oc.y = camera_position.y - sphere->pos.y;
    oc.z = camera_position.z - sphere->pos.z;
    a = dot(ray, ray);
    b = 2 * dot(oc, ray);
    c = dot(oc, oc) - sphere->diameter * sphere->diameter;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (0);
    t = (-b - sqrt(discriminant)) / (2 * a);
    if (t < 0)
        return (0);
    intersection->x = camera_position.x + t * ray.x;
    intersection->y = camera_position.y + t * ray.y;
    intersection->z = camera_position.z + t * ray.z;
    normal->x = intersection->x - sphere->pos.x;
    normal->y = intersection->y - sphere->pos.y;
    normal->z = intersection->z - sphere->pos.z;
    normalize(normal);
    return (1);
}

int dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*int intersect_plane(t_plane *plane, t_vec3 camera_position, t_vec3 ray, t_vec3 *intersection, t_vec3 *normal)
{
    float t;
    float d;
    t_vec3 p0l0;
    t_vec3 n;

    n.x = plane->dir.x;
    n.y = plane->dir.y;
    n.z = plane->dir.z;
    d = -dot(n, plane->pos);
    p0l0.x = camera_position.x - plane->pos.x;
    p0l0.y = camera_position.y - plane->pos.y;
    p0l0.z = camera_position.z - plane->pos.z;
    t = -(dot(n, p0l0) / dot(n, ray));
    if (t < 0)
        return (0);
    intersection->x = camera_position.x + t * ray.x;
    intersection->y = camera_position.y + t * ray.y;
    intersection->z = camera_position.z + t * ray.z;
    normal->x = plane->dir.x;
    normal->y = plane->dir.y;
    normal->z = plane->dir.z;
    normalize(normal);
    return (1);
}*/

void draw_pixel(t_scene *scene, t_vec3 r, t_rgb color)
{
    int index;

    index = (r.y * scene->screen->screen_width + r.x) * 4;
    scene->mlx->img.addr[index] = color.r;
    scene->mlx->img.addr[index + 1] = color.g;
    scene->mlx->img.addr[index + 2] = color.b;
    scene->mlx->img.addr[index + 3] = 0;
}

