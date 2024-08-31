/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/08/31 14:49:32 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

void init_camera(t_scene *scene)
{
    t_screen *screen;
    double new_fov;

    screen = gc_calloc(sizeof(t_screen));
    screen->screen_width = WIDTH;
    screen->screen_height = HEIGHT;
    screen->aspect_ratio = (float)WIDTH / (float)HEIGHT;
    new_fov = scene->cam->fov / 2.0;
    screen->scalar_fov = (scene->cam->fov * M_PI / 180);
    screen->scale = tan((new_fov * 3.1415926535f) / 180.0f);
    screen->aspect_ratio = screen->scale / (16.0 / 9.0);
    screen->right = normalize(merge_vect(scene->cam->dir, (t_vec3){0.0, 1.0, 0.0}));
    screen->up = normalize(merge_vect(scene->cam->dir, screen->right));
    screen->right = normalize(merge_vect(scene->cam->dir, screen->up));
    scene->screen = screen;
}

void render_scene(t_scene *scene)
{
    t_render render;

    ft_memset(&render, 0, sizeof(t_render));
    render.screen = (*scene->screen);
    pixel_draw(scene, &render);
    mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img.img, 0, 0);
    mlx_loop(scene->mlx->mlx);
}


void pixel_draw(t_scene *scene, t_render *render)
{
    size_t x;
    size_t y;

    y = 0;
    init_camera(scene);
    render->prime_ray.origin = scene->cam->pos;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            new_init_camera(scene, &render->prime_ray, (float)x, (float)y);
            render->color_ambiant = color_rgb(ambiant_color(render, scene, 0));
            new_mlx_pixel_put(scene->mlx, x, y, render->color_ambiant);
            x++;
        }
        y++;
    }
}


int	fps_counter_init(t_fpscounter *counter, t_u8b samples)
{
	t_u8b	i;
	t_lst	*snapshot;

	i = 0;
	snapshot = NULL;
	counter->snapshots_samples = samples;
	if (counter->snapshots_samples == 0)
		return (-1);
	while (i++ < counter->snapshots_samples)
	{
		snapshot = lst_new(gc_calloc(sizeof(uint64_t)));
		if (!snapshot)
			return (-1);
		lst_append(&counter->snapshots, snapshot);
	}
	snapshot->next = counter->snapshots;
	counter->snapshots->prev = snapshot;
	return (0);
}

uint64_t	get_time()
{
	static struct timeval	tv;
	static uint64_t			timestamp;

	gettimeofday(&tv, NULL);
	// change multiplication by bitshifting
	timestamp = tv.tv_sec * 1e6 + tv.tv_usec;
	return (timestamp);
}


float	fps_count(t_fpscounter *counter)
{
	static float	result;
	static uint64_t	delta;
	static uint64_t	now;

	// if there now last_tick, set it and skip
	if (!counter->last_tick)
		return (counter->last_tick = get_time(), 0);
	now = get_time();
	// calculate the delta from the difference
	// of the last_tick and the new tick
	//printf("last_tick=%ld\n", counter->last_tick);
	//printf("now      =%ld\n", now);
	delta = now - counter->last_tick;
	//printf("delta=%ld\n", delta);
	*(uint64_t *) counter->snapshots->content = delta;
	// skip for the next snapshot
	counter->snapshots = counter->snapshots->next;
	counter->last_tick = now;
	counter->total += delta;
	//printf("total=%ld\n", counter->total);
	//printf("snapshots=%d\n", counter->current_snapshots);
	// check if the number of snapshots is the same as asked.
	// if not, it return to prevent from substracting the lastest delta
	if (counter->n_snapshots < counter->snapshots_samples)
		return (counter->n_snapshots++,
			1e6 / ((float) counter->total / counter->n_snapshots));
	result = (float) counter->total / counter->n_snapshots;
	counter->total -= *((uint64_t *) counter->snapshots->prev->content);
	return (1e6 / result);
}

void	fps_display(t_mlx *display)
{
	static char	*string;

	string = ft_itoa(fps_count(display->fps_counter));
	mlx_string_put(display->mlx, display->win, 0, 10, WHITE, string);
	gc_free(string);
	string = NULL;
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


t_vec3 new_vector(double x, double y, double z)
{
    t_vec3 new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (new);
}

t_rgb vect_to_rgb(t_vec3 vec)
{
    t_rgb color;

    color.r = (int)vec.x;
    color.g = (int)vec.y;
    color.b = (int)vec.z;
    return (color);
}


int color_rgb(t_rgb color)
{
    return (((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff));
}

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

t_rgb ambiant_color(t_render *render, t_scene *scene, int depth)
{
    t_rgb color;
    t_hit hit;

    ft_memset(&color, 0, sizeof(t_rgb));
    render->obj_closest = intersect(render, scene->obj, &hit);
    if (!render->obj_closest)
        return (color);
    color = light_handler(scene, render, &hit);
    --depth;
    return (color);
}

t_rgb light_handler(t_scene *scene, t_render *render, t_hit *hit)
{
    t_rgb final_color;
    final_color = mult_color_vec4(hit->col, scene->ambient->light_ratio);
    double d;
    t_rgb color;
    if (dot(hit->norm, render->prime_ray.direction) > 0)
        hit->norm = mult_vec3(hit->norm, -1);
    d = dot(hit->norm, new_normalized(sub_vec3(scene->light->pos, hit->hit)));
    if (d < 0)
        d = 0;
    color = vect_to_rgb(vec3_ambiant(hit->col, (t_rgb){255, 255, 255}, d * scene->light->brightness));
    if (new_shadow_ray(scene, hit, render) == true)
        color = mult_rgb(color, 0.2);
    color = add_rgb(final_color, color);
    return (color);
}

t_rgb add_rgb(t_rgb a, t_rgb b)
{
    t_rgb added;

    added.r = check_data(a.r + b.r, 0, 255);
    added.g = check_data(a.g + b.g, 0, 255);
    added.b = check_data(a.b + b.b, 0, 255);
    return (added);
}

t_u8b check_data(int n, int min, int max)
{
    if (n > max)
        return (max);
    else if (n < min)
        return (min);
    return (n);
}



bool new_shadow_ray(t_scene *scene, t_hit *hit, t_render *render)
{
    t_vec3 light_dir;
    t_light *new_light;
    t_ray_view ray;

    new_light = scene->light;
    light_dir = sub_vec3(new_light->pos, hit->hit);
    render->light_distance = vec3_length(light_dir);
    ray.origin = hit->hit;
    ray.direction = new_normalized(light_dir);
    render->prime_ray = ray;
    return (intersect3(render, scene));
}

bool intersect3(t_render *render, t_scene *scene)
{
    double max_distance;
    t_hit tmp_hit;
    t_obj *obj;

    max_distance = render->light_distance;
    tmp_hit.h = INFINITY;
    obj = scene->obj;
    while (obj)
    {
        if (obj->id != render->obj_closest->id)
        {        
            if(new_intersect(render, obj, &tmp_hit) && tmp_hit.h < max_distance && tmp_hit.h > 0.0f)
                return (true);
        }
        obj = obj->next;
    }
    return (false);
}


double vec3_length(t_vec3 vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}


t_rgb mult_rgb(t_rgb ambiant, double intensity)
{
    t_rgb new;
    new.r = check_data(ambiant.r * intensity, 0, 255);
    new.g = check_data(ambiant.g * intensity, 0, 255);
    new.b = check_data(ambiant.b * intensity, 0, 255);
    return (new);
}


t_obj *intersect(t_render *render, t_obj *obj, t_hit *hit)
{
    double min_distance;
    t_obj *obj_closest;
    t_hit tmp_hit;

    min_distance = INFINITY;
    tmp_hit.h = 0;
    obj_closest = NULL;
    while (obj)
    {
        if (new_intersect(render, obj, &tmp_hit))
        {
            if (tmp_hit.h < min_distance)
            {
                min_distance = tmp_hit.h;
                obj_closest = obj;
                *hit = tmp_hit;
            }
        }
        obj = obj->next;
    }
    if (obj_closest)
        hit->col = obj_closest->color;
    return (obj_closest);
}


int new_intersect(t_render *render, t_obj *obj, t_hit *hit)
{
    if (obj->type == 's')
        return (intersect_sphere(&render->prime_ray, &obj->object.sphere, hit));
    else if (obj->type == 'p')
        return (intersect_plane(&render->prime_ray, &obj->object.plane, hit));
    /*else if (obj->type == 'c')
        return (intersect_cylinder(&render->prime_ray, &obj->object.cylinder, hit));*/
    return (0);
}


bool intersect_sphere(t_ray_view *ray, t_sphere *sphere, t_hit *hit)
{
    double a;
    double b;
    double c;
    double delta;
    double radius;
    double t0;

    radius = sphere->diameter / 2.0f;
    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(sub_vec3(ray->origin, sphere->pos), ray->direction);
    c = dot(sub_vec3(ray->origin, sphere->pos), sub_vec3(ray->origin, sphere->pos)) - radius * radius;
    delta = b * b - 4.0f * a * c;
    if (delta >= 0.0f)
    {
        t0 = (-b - sqrt(delta)) / (2.0f * a);
        hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, t0));
        hit->norm = sub_vec3(hit->hit, sphere->pos);
        normalize_bis(&hit->norm);
        hit->h = t0;
        hit->col = sphere->color;
        return (true);
    }
    return (false);
}

bool intersect_plane(t_ray_view *ray, t_plane *plane, t_hit *hit)
{
    double denom;

    denom = dot(plane->dir, ray->direction);
    if (fabs(denom) > 1e-6)
    {
        hit->h = dot(sub_vec3(plane->pos, ray->origin), plane->dir) / denom;
        if (hit->h >= 0)
        {
            hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->h));
            hit->norm = plane->dir;
            if (dot(hit->norm, ray->direction) > 0)
                hit->norm = mult_vec3(hit->norm, -1);
            return (true);
        }
    }
    return (false);
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

t_rgb mult_color_vec4(t_rgb color, double b)
{
    t_rgb mult;

    mult.r = check_data(color.r * b, 0, 255);
    mult.g = check_data(color.g * b, 0, 255);
    mult.b = check_data(color.b * b, 0, 255);
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

t_vec3 new_normalized(t_vec3 new)
{
    t_vec3 normalized;

    normalized = new;
    normalize_bis(&normalized);
    return (normalized);
}

t_vec3 normalize(t_vec3 new)
{
    double length;

    length = 1.0 / sqrt(new.x * new.x + new.y * new.y + new.z * new.z);
    return ((t_vec3){new.x * length, new.y * length, new.z * length});
}

t_vec3 *normalize_bis(t_vec3 *new)
{
    float length;

    length = 1.0 / sqrt(new->x * new->x + new->y * new->y + new->z * new->z);
    new->x *= length;
    new->y *= length;
    new->z *= length;
    return (new);
}


t_vec3 merge_vect(t_vec3 a, t_vec3 b)
{
    t_vec3 merged;

    merged.x = (a.y * b.z) - (a.z * b.y);
    merged.y = (a.z * b.x) - (a.x * b.z);
    merged.z = (a.x * b.y) - (a.y * b.x);
    return (merged);
}

