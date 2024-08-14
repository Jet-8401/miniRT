/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/08/14 16:21:51 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

void init_camera(t_scene *scene)
{
    t_screen *screen;

    screen = gc_calloc(sizeof(t_screen));
    screen->screen_width = WIDTH;
    screen->screen_height = HEIGHT;
    screen->aspect_ratio = (float)WIDTH / (float)HEIGHT;
    screen->scalar_fov = (scene->cam.fov * M_PI / 180);
    screen->scale = tan(screen->scalar_fov / 2.0);
    if (fabs(scene->cam.dir.y) > 1.0 - 1e-4)
        screen->qx = mult_vec3(normalize(merge_vect((t_vec3){0, 0, -1.0}, scene->cam.dir)), screen->scale);
    else
        screen->qx = mult_vec3(normalize(merge_vect((t_vec3){0, 1.0, 0}, scene->cam.dir)), screen->scale);
    screen->qy = mult_vec3(normalize(merge_vect(screen->qx, scene->cam.dir)) ,dot_len(screen->qx) * HEIGHT / WIDTH);
    screen->px = mult_vec3(screen->qx, -2.0 / (screen->screen_width - 1));
    screen->py = mult_vec3(screen->qy, -2.0 / (screen->screen_height - 1));
    screen->pos = add_vec3(add_vec3(scene->cam.pos, scene->cam.dir), add_vec3(screen->qx, screen->qy));
    scene->screen = screen;
}

void render_scene(t_scene *scene)
{
    t_render render;

    render.screen = (*scene->screen);
    pixel_draw(scene, render);
    mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
    mlx_loop(scene->mlx->mlx);
}


void pixel_draw(t_scene *scene, t_render render)
{
    size_t x;
    size_t y;

    y = 0;
    render.ray.origin = scene->cam.pos;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            render.pixel_pos = add_vec3(render.screen.pos, mult_vec3_comb(x + ft_rand(), render.screen.px, render.screen.screen_height - 1 - y + ft_rand(), render.screen.py));
            render.ray.direction = normalize(sub_vec3(render.pixel_pos, render.ray.origin));
            render.color_ambiant = ambiant_color(&render.ray, scene);
            new_mlx_pixel_put(scene->mlx, x, y, new_rgb(render.color_ambiant.x, render.color_ambiant.y, render.color_ambiant.z));
            x++;
        }
        y++;
    }
}

double ft_rand(void)
{
    return (rand() / ((double) RAND_MAX + 1.0));
}

int new_rgb(int r, int g, int b)
{
    return (((r & 0xff)  << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    dst = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
    *(unsigned int *)dst = color;
}*/

void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *pixel;
    int i;

    i = mlx->img.bpp - 8;
    pixel = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
    while (i >= 0)
    {
        if (mlx->img.endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        else
            *pixel++ = (color >> (mlx->img.bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
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
    t_vec3 ret = {0, 0, 0};
    t_vec3 light;
    double h;

    //init_ret(&ret);
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

/*void init_ret(t_vec3 *ret)
{
    (*ret)->x = 0;
    (*ret)->y = 0;
    (*ret)->z = 0;
}*/

int in_scene(t_vec3 ray, t_vec3 norm)
{
    if (dot(ray, norm) > 0)
        return (1);
    return (0);
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
    a = dot(ray->direction, ray->direction) - (dot(ray->direction, n) * dot(ray->direction, n));
    b = 2 * (dot(ray->direction, oc) - (dot(ray->direction, n) * dot(oc, n)));
    c = dot(oc, oc) - (dot(oc, n) * dot(oc, n)) - (cylinder->diameter / 2 * cylinder->diameter / 2);
    delta = b * b - 4 * a * c;
    if (delta < EPSILON)
        return (-1.0);
    h = pick_inter_cylinder(a, b, delta, ray, n, oc, cylinder);
    return (h);
}

double pick_inter_cylinder(double a, double b, double delta, t_ray_view *ray, t_vec3 n, t_vec3 oc, t_cylinder *cylinder)
{
    double num1;
    double num2;
    //double h;
    double x1;
    double x2;

    num1 = (-b * sqrt(delta)) / (2.0 * a);
    num2 = (-b * sqrt(delta)) / (2.0 * a);
    if (num1 < EPSILON)
        return (-1.0);
    /*if (num1 > num2)
        h = num2;
    else
        h = num1;*/
    x1 = dot(ray->direction, n) * num2 + dot(oc, n);
    x2 = dot(ray->direction, n) * num1 + dot(oc, n);
    if (x1 >= EPSILON && x1 <= cylinder->height)
        return (num2);
    if (x2 >= EPSILON && x2 <= cylinder->height)
        return (num1);
    return (-1);
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
        t = dot(oc, n);
        t = -t / d;
        if (t < EPSILON)
            return (-1.0);
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
    //double h;
    double num1;
    double num2;

    oc = sub_vec3(ray->origin, sphere->pos);
    a = dot(ray->direction, ray->direction);
    b = 2 * dot(oc, ray->direction);
    c = dot(oc, oc) - (sphere->diameter / 2.0) * (sphere->diameter / 2.0);
    delta = b * b - (4 * a * c);
    if (delta < EPSILON)
        return (-1.0);
    num1 = (b * (-1.0) - sqrt(delta)) / (2.0 * a);
    num2 = (b * (-1.0) + sqrt(delta)) / (2.0 * a);
    if (num1 * num2 > EPSILON)
    {
        if (num1 > EPSILON)
            return (num1 > num2 ? num2 : num1);
        return (-1);
    }
    if (num1 > EPSILON)
        return (num1);
    return (num2);
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

t_vec3 mult_vec3_comb(double a_1, t_vec3 a, double b_1, t_vec3 b)
{
    return (add_vec3(mult_vec3(a, a_1), mult_vec3(b, b_1)));
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

double dot_len(t_vec3 a)
{
    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3 new_normalized(t_vec3 new)
{
    t_vec3 normalized;

    normalized = new;
    normalize(&normalized);
    return (normalized);
}

t_vec3 normalize(t_vec3 new)
{
    double length;

    length = 1.0 / sqrt(new.x * new.x + new.y * new.y + new.z * new.z);
    return ((t_vec3){new.x * length, new.y * length, new.z * length});
}

t_vec3 merge_vect(t_vec3 a, t_vec3 b)
{
    t_vec3 merged;

    merged.x = (a.y * b.z) - (a.z * b.y);
    merged.y = (a.x * b.z) - (a.z * b.x);
    merged.z = (a.x * b.y) - (a.y * b.x);
    return (merged);
}

