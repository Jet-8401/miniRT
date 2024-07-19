/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/19 04:48:56 by akinzeli         ###   ########.fr       */
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
    scene->screen->forward = scene->cam.dir;
    scene->screen->forward.x += 0.0001;
    scene->screen->camera_position = scene->cam.pos;
    scene->screen->up = new_normalized(merge_vect(scene->screen->forward, (t_vec3){0, 1, 0}));
    scene->screen->right = new_normalized(merge_vect(scene->screen->forward, scene->screen->up));
}

void render_scene(t_scene *scene)
{
    t_render render;

    render.screen = *(scene)->screen;
    pixel_draw(scene, render);
    mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
    mlx_loop(scene->mlx->mlx);
}


void pixel_draw(t_scene *scene, t_render render)
{
    size_t x;
    size_t y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            render.a = (double)x * 2 / WIDTH - 1;
            render.b = (double)y * 2 / HEIGHT - 1;
            render.ray = new_ray(scene, render);
            render.color_ambiant = ambiant_color(&render.ray, scene);
            new_mlx_pixel_put(scene->mlx, x, y, new_rgb(render.color_ambiant.x, render.color_ambiant.y, render.color_ambiant.z));
            x++;
        }
        y++;
    }
}

int new_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    dst = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
    *(unsigned int *)dst = color;
}

t_vec3 ambiant_color(t_ray_view *ray, t_scene *scene)
{
    t_vec3 color;
    t_vec3 light_dir;
    t_hit hit;

    hit = intersect(ray, scene);
    if (hit.h > EPSILON)
    {
        light_dir = vec3_ambiant(hit.col, scene->ambient.color, scene->ambient.light_ratio);
        if (in_scene(ray->direction, hit.norm))
            hit.norm = mult_vec3(hit.norm, -1);
        color = new_color(scene, hit, light_dir);
        return (color);
    }
    return (mult_color_vec3(scene->ambient.color, scene->ambient.light_ratio));
}

t_hit intersect(t_ray_view *ray, t_scene *scene)
{
    t_hit hit;
    
    hit.h = -1.0;
    while (scene->sphere)
    {
        hit = intersect_sphere(ray, scene->sphere, hit);
        scene->sphere = scene->sphere->next;
    }
    while (scene->plane)
    {
        hit = intersect_plane(ray, scene->plane, hit);
        scene->plane = scene->plane->next;
    }
    while (scene->cylinder)
    {
        hit = intersect_cylinder(ray, scene->cylinder, hit);
        scene->cylinder = scene->cylinder->next;
    }
    return (hit);
}

t_vec3 new_color(t_scene *scene, t_hit hit, t_vec3 light_dir)
{
    t_vec3 ret;
    t_vec3 light;
    double h;

    init_ret(&ret);
    if (new_shader(scene, hit, scene->light))
        ret = add_color(ret, light_dir);
    else
    {
        light = sub_vec3(scene->light->pos, hit.hit);
        h = dot(new_normalized(light), hit.norm);
        ret = add_color(ret, light_dir);
        if (h > 0)
            ret = add_color(ret, share_light(hit, scene->light, h));
    }
    return (ret);
}

t_vec3 share_light(t_hit hit, t_light *light, double h)
{
    t_vec3 share;

    share = vec3_ambiant(hit.col, (t_rgb){255, 255, 255}, h * light->brightness);
    return (share);
}

t_vec3 add_color(t_vec3 a, t_vec3 b)
{
    t_vec3 added;

    added.x = a.x + b.x;
    added.y = a.y + b.y;
    added.z = a.z + b.z;
    if (added.x > 255)
        added.x = 255;
    if (added.y > 255)
        added.y = 255;
    if (added.z > 255)
        added.z = 255;
    return (added);
}

int new_shader(t_scene *scene, t_hit hit, t_light *light)
{
    t_ray_view ray;
    t_vec3 in_light;
    t_vec3 in_shadow;
    t_hit tmp;

    in_light = sub_vec3(light->pos, hit.hit);
    ray.origin = hit.hit;
    ray.direction = new_normalized(in_light);
    tmp = intersect(&ray, scene);
    in_shadow = sub_vec3(tmp.hit, ray.origin);
    if (tmp.h > EPSILON && (final_shadow(in_shadow) < final_shadow(in_light)))
        return (1);
    return (0);
}


double final_shadow(t_vec3 in)
{
    return (sqrt(pow(in.x, 2) + pow(in.y, 2) + pow(in.z, 2)));
}

void init_ret(t_vec3 *ret)
{
    ret->x = 0;
    ret->y = 0;
    ret->z = 0;
}

int in_scene(t_vec3 ray, t_vec3 norm)
{
    return (dot(ray, norm) > 0);
}

t_hit intersect_sphere(t_ray_view *ray, t_sphere *sphere, t_hit hit)
{
    t_hit tmp;

    tmp.h = sphere_inside(ray, sphere);
    if ((hit.h == -1.0 || hit.h > tmp.h) && tmp.h > EPSILON)
    {
        hit.col = sphere->color;
        hit.hit = add_vec3(ray->origin, mult_vec3(ray->direction, tmp.h));
        hit.norm = new_normalized(sub_vec3(hit.hit, sphere->pos));
        hit = tmp;
    }
    return (hit);
}

t_hit intersect_plane(t_ray_view *ray, t_plane *plane, t_hit hit)
{
    t_hit tmp;
    
    tmp.h = plane_inside(ray, plane);
    if ((hit.h == -1.0 || hit.h > tmp.h) && tmp.h > EPSILON)
    {
        hit.col = plane->color;
        hit.hit = add_vec3(ray->origin, mult_vec3(ray->direction, tmp.h));
        hit.norm = plane->dir;
        if (dot(hit.norm, ray->direction) > __DBL_EPSILON__)
            hit.norm = mult_vec3(hit.norm, -1);
        hit = tmp;
    }
    return (hit);
}

t_hit intersect_cylinder(t_ray_view *ray, t_cylinder *cylinder, t_hit hit)
{
    t_hit tmp;
    double h;
    t_vec3 new;

    tmp.h = cylinder_inside(ray, cylinder);
    if ((hit.h == -1.0 || hit.h > tmp.h) && tmp.h > EPSILON)
    {
        hit.col = cylinder->color;
        hit.hit = add_vec3(ray->origin, mult_vec3(ray->direction, tmp.h));
        new = new_normalized(cylinder->dir);
        h = dot(sub_vec3(ray->origin, cylinder->pos), new) + dot(ray->direction, mult_vec3(new, tmp.h));
        hit.norm = new_normalized(sub_vec3(sub_vec3(hit.hit, cylinder->pos), mult_vec3(new, h)));
        hit = tmp;
    }
    return (hit);
}

double cylinder_inside(t_ray_view *ray, t_cylinder *cylinder)
{
    double a;
    double b;
    double c;
    double delta;
    double h;
    t_vec3 oc;
    t_vec3 n;

    n = new_normalized(cylinder->dir);
    oc = sub_vec3(ray->origin, cylinder->pos);
    a = dot(ray->direction, ray->direction) - pow(dot(ray->direction, n), 2);
    b = 2 * (dot(ray->direction, oc) - dot(ray->direction, n) * dot(oc, n));
    c = dot(oc, oc) - pow(dot(oc, n), 2) - pow(cylinder->diameter / 2, 2);
    delta = b * b - 4 * a * c;
    if (delta < EPSILON)
        return (-1.0);
    h = (-b - sqrt(delta)) / (2 * a);
    if (h < EPSILON)
        h = (-b + sqrt(delta)) / (2 * a);
    return (h);
}


double plane_inside(t_ray_view *ray, t_plane *plane)
{
    //double h;
    double d;
    double t;
    t_vec3 oc;
    t_vec3 n;

    n = new_normalized(plane->dir);
    oc = sub_vec3(ray->origin, plane->pos);
    d = dot(ray->direction, n);
    if (d != 0)
    {
        t = -dot(oc, n) / d;
        if (t > EPSILON)
            return (t);
    }
    return (-1.0);
}



double sphere_inside(t_ray_view *ray, t_sphere *sphere)
{
    t_vec3 oc;
    double a;
    double b;
    double c;
    double delta;
    double h;

    oc = sub_vec3(ray->origin, sphere->pos);
    a = dot(ray->direction, ray->direction);
    b = 2 * dot(oc, ray->direction);
    c = dot(oc, oc) - sphere->diameter * sphere->diameter;
    delta = b * b - (4 * a * c);
    if (delta < EPSILON)
        return (-1.0);
    h = (-b - sqrt(delta)) / (2 * a);
    if (h < EPSILON)
        h = (-b + sqrt(delta)) / (2 * a);
    return (h);
}

t_vec3 vec3_ambiant(t_rgb col, t_rgb color, float light_ratio)
{
    t_vec3 ambiant;

    ambiant.x = col.r * (color.r / 255) * light_ratio;
    ambiant.y = col.g * (color.g / 255) * light_ratio;
    ambiant.z = col.b * (color.b / 255) * light_ratio;
    return (ambiant);
}

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 added;

    added.x = a.x + b.x;
    added.y = a.y + b.y;
    added.z = a.z + b.z;
    return (added);
}
t_vec3 mult_color_vec3(t_rgb color, double b)
{
    t_vec3 mult;

    mult.x = color.r * b;
    mult.y = color.g * b;
    mult.z = color.b * b;
    return (mult);
}

t_vec3 mult_vec3(t_vec3 a, double b)
{
    t_vec3 mult;

    mult.x = a.x * b;
    mult.y = a.y * b;
    mult.z = a.z * b;
    return (mult);
}

t_vec3 sub_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 sub;

    sub.x = a.x - b.x;
    sub.y = a.y - b.y;
    sub.z = a.z - b.z;
    return (sub);
}

double dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}


t_ray_view new_ray(t_scene *scene, t_render render)
{
    t_ray_view ray;

    ray.origin = scene->cam.pos;
    ray.direction = add_vec3(add_vec3(mult_vec3(scene->screen->up, render.a * scene->screen->screen_height), mult_vec3(scene->screen->right, render.b * scene->screen->screen_width)), scene->screen->forward);
    ray.direction = new_normalized(ray.direction);
    return (ray);
}

t_vec3 new_normalized(t_vec3 new)
{
    t_vec3 normalized;

    normalized = new;
    normalize(&normalized);
    return (normalized);
}

void normalize(t_vec3 *new)
{
    double length;

    length = sqrt(new->x * new->x + new->y * new->y + new->z * new->z);
    new->x /= length;
    new->y /= length;
    new->z /= length;
}

t_vec3 merge_vect(t_vec3 a, t_vec3 b)
{
    t_vec3 merged;

    merged.x = (a.y * b.z) - (a.z * b.y);
    merged.y = (a.x * b.z) - (a.z * b.x);
    merged.z = (a.x * b.y) - (a.y * b.x);
    return (merged);
}