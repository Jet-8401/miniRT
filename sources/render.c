/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/08/21 16:59:22 by akinzeli         ###   ########.fr       */
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
    screen->scalar_fov = (scene->cam->fov * M_PI / 180);
    screen->scale = tan(scene->cam->fov / 2 * M_PI / 180);
    //printf("screen cam.dir: %f %f %f\n", scene->cam.dir.x, scene->cam.dir.y, scene->cam.dir.z);
    if (fabs(scene->cam->dir.y) > 1.0 - 1e-4)
        screen->qx = mult_vec3(normalize(merge_vect((t_vec3){0, 0, -1.0}, scene->cam->dir)), screen->scale);
    else
        screen->qx = mult_vec3(normalize(merge_vect((t_vec3){0, 1.0, 0}, scene->cam->dir)), screen->scale);
    screen->qy = mult_vec3(normalize(merge_vect(screen->qx, scene->cam->dir)) ,dot_len(screen->qx) * HEIGHT / WIDTH);
    screen->px = mult_vec3(screen->qx, -2.0 / (screen->screen_width - 1));
    screen->py = mult_vec3(screen->qy, -2.0 / (screen->screen_height - 1));
    screen->pos = add_vec3(add_vec3(scene->cam->pos, scene->cam->dir), add_vec3(screen->qx, screen->qy));
    cam_dir(scene);
    /*printf("screen.pos a init camera: %f %f %f\n", screen->pos.x, screen->pos.y, screen->pos.z);
    printf("screen.px a init camera: %f %f %f\n", screen->px.x, screen->px.y, screen->px.z);
    printf("screen.py a init camera: %f %f %f\n", screen->py.x, screen->py.y, screen->py.z);
    printf("screen.qx a init camera: %f %f %f\n", screen->qx.x, screen->qx.y, screen->qx.z);
    printf("screen.qy a init camera: %f %f %f\n", screen->qy.x, screen->qy.y, screen->qy.z);
    printf("screen.scale a init camera: %f\n", screen->scale);
    printf("screen.scalar_fov a init camera: %f\n", screen->scalar_fov);
    printf("screen.aspect_ratio a init camera: %f\n", screen->aspect_ratio);*/
    scene->screen = screen;
    //render->screen = *screen;
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
            //render->pixel_pos = add_vec3(render->screen.pos, mult_vec3_comb(x + ft_rand(), render->screen.px, render->screen.screen_height - 1 - y + ft_rand(), render->screen.py));
            //render->prime_ray.direction = normalize(sub_vec3(render->pixel_pos, render->prime_ray.origin));
            //printf("ray.direction: %f %f %f\n", render->prime_ray.direction.x, render->prime_ray.direction.y, render->prime_ray.direction.z);
            render->color_ambiant = color_rgb(ambiant_color(render, scene, 0));
            if (render->color_ambiant != 0)
                printf("color_ambiant: %d\n", render->color_ambiant);
            new_mlx_pixel_put(scene->mlx, x, y, render->color_ambiant);
            x++;
        }
        y++;
    }
    //fps_display(scene->mlx);
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
    //t_vec3 coord;

    tmp_scene = scene;
    prime_ray->origin = new_vector(tmp_scene->cam->pos.x, tmp_scene->cam->pos.y, tmp_scene->cam->pos.z);
    /*coord = new_vector(x / tmp_scene->screen->screen_width, y / tmp_scene->screen->screen_height, tmp_scene->screen->aspect_ratio);
    coord.x = coord.x * 2.0f - 1.0f;
    coord.y = coord.y * 2.0f - 1.0f;
    coord.x *= tmp_scene->screen->aspect_ratio;
    prime_ray->direction = new_vector(coord.x, coord.y, -1.0f);*/
    prime_ray->direction.x = (2.0 * (x + 0.5) / (float)WIDTH - 1.0) * tmp_scene->screen->aspect_ratio * tmp_scene->screen->scale;
    prime_ray->direction.y = (1.0 - 2.0 * (y + 0.5) / (float)HEIGHT) * tmp_scene->screen->scale;;
    prime_ray->direction.z = -1.0f;
    //prime_ray->direction = world_cam(scene->cam_matrix, &prime_ray->direction);
    normalize_bis(&prime_ray->direction);
}

t_vec3 world_cam(double cam_matrix[4][4], t_vec3 *direction)
{
    t_vec3 new;

    new.x = cam_matrix[0][0] * direction->x + cam_matrix[1][0] * direction->y + cam_matrix[2][0] * direction->z;
    new.y = cam_matrix[0][1] * direction->x + cam_matrix[1][1] * direction->y + cam_matrix[2][1] * direction->z;
    new.z = cam_matrix[0][2] * direction->x + cam_matrix[1][2] * direction->y + cam_matrix[2][2] * direction->z;
    return (new);
}

void cam_dir(t_scene *scene)
{
    t_vec3 forward;
    t_vec3 right;
    t_vec3 up;
    t_vec3 tmp;

    tmp = new_vector(0, 1, 0);
    forward = scene->cam->dir;
    normalize_bis(&forward);
    right = merge_vect(forward, tmp);
    up = merge_vect(right, forward);
    scene->cam_matrix[0][0] = right.x;
    scene->cam_matrix[0][1] = right.y;
    scene->cam_matrix[0][2] = right.z;
    scene->cam_matrix[1][0] = up.x;
    scene->cam_matrix[1][1] = up.y;
    scene->cam_matrix[1][2] = up.z;
    scene->cam_matrix[2][0] = forward.x;
    scene->cam_matrix[2][1] = forward.y;
    scene->cam_matrix[2][2] = forward.z;
}

t_vec3 new_vector(double x, double y, double z)
{
    t_vec3 new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (new);
}

t_rgb new_color_rgb(double r, double g, double b)
{
    t_rgb new;

    new.r = r;
    new.g = g;
    new.b = b;
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

double ft_rand(void)
{
    return (rand() / ((double) RAND_MAX + 1.0));
}

int new_rgb(int r, int g, int b)
{
    return (((r & 0xff)  << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int color_rgb(t_rgb color)
{
    return (((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff));
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

t_rgb ambiant_color(t_render *render, t_scene *scene, int depth)
{
    t_rgb color;
    //int max_ray;
    //t_obj *o;
    t_hit hit;

    //max_ray = 5;
    ft_memset(&color, 0, sizeof(t_rgb));
    render->obj_closest = intersect(render, scene->obj, &hit);
    if (render->obj_closest)
        printf("closest obj: %c\n", render->obj_closest->type);
    //else
        //printf("closest obj: NULL\n");
    //o = render->obj_closest;
    if (!render->obj_closest)
        return (color);
    color = light_handler(scene, render, &hit);
    //printf("closest obj: %c\n", render->obj_closest->type);
    //printf("Mais ici je passe qu'une fois\n");
    --depth;
    //if (depth < 0)
        //o = NULL;
    //color = o->color;
    //printf("color: %d\n", color_rgb(render->obj_closest->color));
    return (color);
}

t_rgb light_handler(t_scene *scene, t_render *render, t_hit *hit)
{
    t_rgb final_color;
    t_light *new_light;

    (void)render;
    new_light = scene->light;
    final_color = mult_color_vec4(hit->col, scene->ambient->light_ratio);
    if (new_light && !new_shadow_ray(scene, hit))
        final_color = add_rgb(final_color, diffuse_light(new_light, hit, new_light->brightness));
    return (final_color);
    //double d;
    //t_rgb color;
    /*t_rgb ambiant_light;
    t_rgb diffuse;
    t_rgb specular;
    int in_shadow;

    (void)render;
    in_shadow = 0;
    ft_memset(&diffuse, 0, sizeof(diffuse));
    ft_memset(&specular, 0, sizeof(specular));
    ambiant_light = hit->col;
    ambiant_light = add_all_light(ambiant_light, scene->ambient->color, scene->ambient->light_ratio);
    in_shadow = new_shadow_ray(scene, render, hit);
    if (dot(hit->norm, render->prime_ray.direction) > 0)
        hit->norm = mult_vec3(hit->norm, -1);
    d = dot(hit->norm, new_normalized(sub_vec3(scene->light->pos, hit->hit)));
    if (d < 0)
        d = 0;
    color = vect_to_rgb(vec3_ambiant(hit->col, (t_rgb){255, 255, 255}, d * scene->light->brightness));
    if (!in_shadow)
        diffuse = mix_color(diffuse, 1, diffuse_light(scene, render, hit), 1);
    if (!in_shadow)
        specular = mix_color(specular, 1, specular_light(scene, render, hit), 1);
    color = add_all_light(color, scene->ambient->color, scene->ambient->light_ratio);
    return (final_light(ambiant_light, diffuse, specular));*/
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


t_rgb diffuse_light(t_light *light, t_hit *hit, double ratio)
{
    t_vec3 light_dir;
    t_rgb diff_color;
    double cos_angle;
    double diffuse_ratio;
    double attenuation;

    light_dir = sub_vec3(light->pos, hit->hit);
    attenuation = MIN(1.0, 90.0 / vec3_length(light_dir));
    cos_angle = vec3_cossine(hit->norm, light_dir);
    diffuse_ratio = ratio * cos_angle * attenuation;
    diff_color = mult_rgb(hit->col, diffuse_ratio);
    return (diff_color);
    /*t_rgb color;
    double hit_p;

    (void)render;
    color = hit->col;
    hit_p = dot(hit->shadow_ray.direction, hit->norm);
    color = add_all_light(color, (t_rgb){255, 255, 255}, scene->light->brightness * hit_p);
    return (color);*/
}


double vec3_cossine(t_vec3 v1, t_vec3 v2)
{
    double dot_new;
    double lengths; 

    dot_new = dot(v1, v2);
    lengths = vec3_length(v1) * vec3_length(v2);
    return (dot_new / lengths);
}

t_rgb specular_light(t_scene *scene, t_render *render, t_hit *hit)
{
    double hit_p;
    t_rgb specular_color;
    t_vec3 spec;

    hit_p = dot(hit->shadow_ray.direction, hit->norm);
    spec = mult_vec3(hit->norm, hit_p * 2);
    spec = sub_vec3(spec, hit->shadow_ray.direction);
    hit_p = dot(spec, render->prime_ray.direction);
    specular_color = new_color_rgb(255, 255, 255);
    specular_color = add_all_light(specular_color, specular_color, scene->light->brightness * hit_p);
    return (specular_color);
}

t_rgb final_light(t_rgb ambiant_light, t_rgb diffuse, t_rgb specular)
{
    t_rgb final;

    final.r = ambiant_light.r + diffuse.r + specular.r;
    final.g = ambiant_light.g + diffuse.g + specular.g;
    final.b = ambiant_light.b + diffuse.b + specular.b;
    if (final.r > 255)
        final.r = 255;
    if (final.g > 255)
        final.g = 255;
    if (final.b > 255)
        final.b = 255;
    return (final);
}

t_rgb mix_color(t_rgb a, double d1, t_rgb b, double d2)
{
    t_rgb dst;

    dst.r = a.r * d1 + b.r * d2;
    dst.g = a.g * d1 + b.g * d2;
    dst.b = a.b * d1 + b.b * d2;
    if (dst.r > 255)
        dst.r = 255;
    if (dst.g > 255)
        dst.g = 255;
    if (dst.b > 255)
        dst.b = 255;
    return (dst);
}

bool new_shadow_ray(t_scene *scene, t_hit *hit)
{
    t_vec3 light_dir;
    t_light *new_light;
    t_ray_view ray;
    double light_distance;

    new_light = scene->light;
    light_dir = sub_vec3(new_light->pos, hit->hit);
    light_distance = vec3_length(light_dir);
    ray.origin = add_vec3(hit->hit, (t_vec3){0.0001, 0.0001, 0.0001});
    ray.direction = normalize(light_dir);
    return (intersect3(&ray, scene->obj, hit, light_distance));
    /*hit->shadow_ray.origin = hit->hit;
    hit->shadow_ray.direction = new_normalized(sub_vec3(scene->light->pos, hit->hit));
    normalize_bis(&hit->shadow_ray.direction);
    mult_shadow(&hit->shadow_ray.origin, &hit->shadow_ray, 0.01);
    return (intersect2(&hit->shadow_ray, scene->obj, &render->hit_shadow) && distance(hit->shadow_ray.origin, scene->light->pos) > distance(render->hit_shadow.hit, hit->shadow_ray.origin));*/
}

bool intersect3(t_ray_view *render, t_obj *obj, t_hit *hit, double light_distance)
{
    double min_distance;
    t_obj *obj_closest;
    t_hit tmp_hit;

    (void)hit;
    min_distance = light_distance;
    tmp_hit.h = 0;
    obj_closest = NULL;
    while (obj)
    {
        if (new_intersect2(render, obj, &tmp_hit))
        {
            if (tmp_hit.h < min_distance)
            {
                return (true);
            }
        }
        obj = obj->next;
    }
    return (false);
}

double vec3_length(t_vec3 vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

double distance(t_vec3 a, t_vec3 b)
{
    double x;
    double y;
    double z;

    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
    x = pow(x, 2);
    y = pow(y, 2);
    z = pow(z, 2);
    return (sqrt(x + y + z));
}

t_vec3 *mult_shadow(t_vec3 *dst, t_ray_view *ray, double t)
{
    dst->x = ray->origin.x + t * ray->direction.x;
    dst->y = ray->origin.y + t * ray->direction.y;
    dst->z = ray->origin.z + t * ray->direction.z;
    return (dst);
}



t_rgb mult_rgb2(t_rgb a, t_rgb b)
{
    return ((t_rgb){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_rgb mult_rgb(t_rgb ambiant, double intensity)
{
    return ((t_rgb){ambiant.r * intensity, ambiant.g * intensity, ambiant.b * intensity});
}

t_rgb add_all_light(t_rgb color, t_rgb ambiant, float light_ratio)
{
    t_rgb new;

    if (light_ratio > 1)
        light_ratio = 1;
    if (light_ratio < 0)
        light_ratio = 0;
    new.r = color.r * ambiant.r * light_ratio;
    new.g = color.g * ambiant.g * light_ratio;
    new.b = color.b * ambiant.b * light_ratio;
    if (new.r > 255)
        new.r = 255;
    if (new.g > 255)
        new.g = 255;
    if (new.b > 255)
        new.b = 255;
    if (new.r < 0)
        new.r = 0;
    if (new.g < 0)
        new.g = 0;
    if (new.b < 0)
        new.b = 0;
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
                //printf("tmp_hit.h: %f\n", tmp_hit.h);
            }
        }
        obj = obj->next;
    }
    if (obj_closest)
        hit->col = obj_closest->color;
    return (obj_closest);
}


t_obj *intersect2(t_ray_view *render, t_obj *obj, t_hit *hit)
{
    double min_distance;
    t_obj *obj_closest;
    t_hit tmp_hit;

    min_distance = INFINITY;
    tmp_hit.h = 0;
    obj_closest = NULL;
    while (obj)
    {
        if (new_intersect2(render, obj, &tmp_hit))
        {
            if (tmp_hit.h < min_distance)
            {
                min_distance = tmp_hit.h;
                obj_closest = obj;
                *hit = tmp_hit;
                //printf("tmp_hit.h: %f\n", tmp_hit.h);
            }
        }
        obj = obj->next;
    }
    if (obj_closest)
        hit->col = obj_closest->color;
    return (obj_closest);
}


int new_intersect2(t_ray_view *render, t_obj *obj, t_hit *hit)
{
    //printf("obj->type: %c\n", obj->type);
    if (obj->type == 's')
        return (intersect_sphere(render, &obj->object.sphere, hit));
    else if (obj->type == 'p')
        return (intersect_plane(render, &obj->object.plane, hit));
    /*else if (obj->type == 'c')
        return (intersect_cylinder(&render->ray, &obj->object.cylinder, *hit));*/
    return (0);
}

int new_intersect(t_render *render, t_obj *obj, t_hit *hit)
{
    //printf("obj->type: %c\n", obj->type);
    if (obj->type == 's')
        return (intersect_sphere(&render->prime_ray, &obj->object.sphere, hit));
    else if (obj->type == 'p')
        return (intersect_plane(&render->prime_ray, &obj->object.plane, hit));
    /*else if (obj->type == 'c')
        return (intersect_cylinder(&render->ray, &obj->object.cylinder, *hit));*/
    return (0);
}

/*t_vec3 new_color(t_scene *scene, t_hit hit, t_vec3 light_dir)
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
}*/

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

/*int new_shader(t_scene *scene, t_hit hit, t_light *light)
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
}*/


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

bool intersect_sphere(t_ray_view *ray, t_sphere *sphere, t_hit *hit)
{
    //t_vec3 oc;
    double a;
    double b;
    double c;
    double delta;
    double radius;
    double t0;
    //double t1;

    radius = sphere->diameter / 2.0f;
    //oc = sub_vec3(ray->origin, sphere->pos);
    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(sub_vec3(ray->origin, sphere->pos), ray->direction);
    c = dot(sub_vec3(ray->origin, sphere->pos), sub_vec3(ray->origin, sphere->pos)) - radius * radius;

    delta = b * b - 4.0f * a * c;
    if (delta >= 0.0f)
    {
        t0 = (-b - sqrt(delta)) / (2.0f * a);
        //t1 = (-b + sqrt(delta)) / (2.0f * a);
        hit->hit = add_vec3(sub_vec3(ray->origin, sphere->pos), mult_vec3(ray->direction, t0));
        hit->norm = sub_vec3(hit->hit, sphere->pos);
        normalize_bis(&hit->norm);
        hit->h = t0;
        return (true);
    }
    return (false);

    /*oc = sub_vec3(ray->origin, sphere->pos); 
    a = dot(oc, ray->direction);
    //printf("sphere diameter: %f\n", sphere->diameter);
    radius = pow(sphere->diameter / 2, 2);
    //printf("radius: %f\n", radius);
    //printf("a: %f\n", a);
    //printf("oc: %f %f %f\n", oc.x, oc.y, oc.z);
    if (a < 0)
        return (false);
    b = dot(oc, oc) - a * a;
    //printf("b: %f\n", b);
    if (b > radius) 
        return (false);
    c = sqrt(radius - b);
    hit->h = a - c;
    delta = a + c;
    //printf("c: %f\n", c);
    //printf("hit.h: %f\n", hit->h);
    //printf("delta: %f\n", delta);
    if (hit->h < EPSILON && delta < EPSILON)
        return (false);
    if (hit->h < EPSILON || hit->h > delta)
        hit->h = delta;
    hit->hit = mult_vec3(ray->direction, hit->h);
    hit->norm = sub_vec3(sphere->pos, hit->hit);
    normalize_bis(&hit->norm);
    return (true);*/
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

/*t_hit intersect_cylinder(t_ray_view *ray, t_cylinder *cylinder, t_hit hit)
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
}*/

/*double cylinder_inside(t_ray_view *ray, t_cylinder *cylinder)
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
    if (num1 > num2)
        h = num2;
    else
        h = num1;
    x1 = dot(ray->direction, n) * num2 + dot(oc, n);
    x2 = dot(ray->direction, n) * num1 + dot(oc, n);
    if (x1 >= EPSILON && x1 <= cylinder->height)
        return (num2);
    if (x2 >= EPSILON && x2 <= cylinder->height)
        return (num1);
    return (-1);
}*/


/*double plane_inside(t_ray_view *ray, t_plane *plane)
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
}*/


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

t_rgb mult_color_vec4(t_rgb color, double b)
{
    t_rgb mult;

    mult.r = color.r * b;
    mult.g = color.g * b;
    mult.b = color.b * b;
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
    merged.y = (a.x * b.z) - (a.z * b.x);
    merged.z = (a.x * b.y) - (a.y * b.x);
    return (merged);
}

