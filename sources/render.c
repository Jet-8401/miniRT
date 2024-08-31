#include "../headers/minirt.h"

// quadratic formula
// -b - sqrt((b * b) - 4.0f * a * c) / (2.0f * a)

float	solve_quadratic(float a, float b, float c)
{
	float	discriminant;

	discriminant = (b * b) - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (discriminant);
	return (-b - sqrt(discriminant) / (2.0f * a));
}

/*

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

*/

// t = -X|V / D|V
bool	plane_equ(t_object *plane, t_ray *ray, t_form_hit *hit)
{
	float	denominator;
	t_vec3	p0l0 = {0, 0, 0};

	(void) hit;
	denominator = vec3D_dot(&plane->dir, &ray->dir);
	if (denominator > 0.0f)
	{
		vec3D_subtract(&plane->pos, &ray->origin, &p0l0);
		return (vec3D_dot(&p0l0, &plane->dir) / denominator);
	}
	return (0);
}

bool	sphere_equ(t_object *sphere, t_ray *ray, t_form_hit *hit)
{
	float	a, b, c;
	t_vec3	newOrigin = {0, 0, 0};

	vec3D_subtract(&ray->origin, &sphere->pos, &newOrigin);

	a = vec3D_dot(&ray->dir, &ray->dir);
	b = 2.0f * vec3D_dot(&newOrigin, &ray->dir);
    c = vec3D_dot(&newOrigin, &newOrigin) - sphere->radius * sphere->radius;

    hit->t = solve_quadratic(a, b, c);
    if (hit->t < 0.0f)
    	return (false);

    vec3D_mult(&ray->dir, hit->t, &hit->hit);
    vec3D_add(&ray->origin, &hit->hit, &hit->hit);
    vec3D_subtract(&hit->hit, &sphere->pos, &hit->norm);
    vec3D_normalize(&hit->norm);
	return (true);
}

// P - C = D*t + X
// P=center
// O=ray origin
// D=ray direction
// X=O - C
// V is a unit length vector that determines cylinder's axis
//	a   = D|D - (D|V)^2
//	b/2 = D|X - (D|V)*(X|V)
//	c   = X|X - (X|V)^2 - r*r
bool	cylinder_equ(t_object *cy, t_ray *ray, t_form_hit *hit)
{
	float	a, b, c;
	t_vec3	X = {0, 0, 0};
	t_vec3	C = {
		cy->pos.x - cy->height / 2 * ray->dir.x,
		cy->pos.y - cy->height / 2 * ray->dir.y,
		cy->pos.z - cy->height / 2 * ray->dir.z
	};

	(void) hit;
	// cap1 = center - height/2 * Normal Vector
	vec3D_subtract(&ray->origin, &C, &X);

	a = vec3D_dot(&ray->dir, &ray->dir) - pow(vec3D_dot(&ray->dir, &cy->dir), 2);
	b = vec3D_dot(&ray->dir, &X) -
		(vec3D_dot(&ray->dir, &cy->dir) * vec3D_dot(&X, &cy->dir));
	b *= 2;
	c = vec3D_dot(&X, &X) - pow(vec3D_dot(&X, &cy->dir), 2) -
		(cy->radius * cy->radius);

	return (solve_quadratic(a, b, c));
}

bool	instersect_forms(t_scene *scene, t_ray *ray, t_form_hit *hit)
{
	static bool	(*equations[3])(t_object *, t_ray *, t_form_hit *) = {
		sphere_equ, plane_equ, cylinder_equ
	};
	t_object		*obj;
	float			closest_distance;
	bool			has_hit;

	obj = scene->objects;
	closest_distance = 3.402823466e+38F;
	has_hit = 0;
	while (obj)
	{
		if (equations[obj->type](obj, ray, hit) && hit->t < closest_distance)
		{
			has_hit = 1;
			closest_distance = hit->t;
			hit->color = &obj->color;
		}
		obj = obj->next;
	}
	return (has_hit);
}

void init_camera(t_scene *scene)
{
    scene->display.scale = tan(((float) scene->cam->fov / 2 * 3.1415926535f) / 180);
    scene->display.aspect_ratio = scene->display.scale / (16.0 / 9.0);
    scene->display.right = normalize(merge_vect(scene->cam->dir, (t_vec3){0.0, 1.0, 0.0}));
    scene->display.up = normalize(merge_vect(scene->cam->dir, scene->display.right));
    scene->display.right = normalize(merge_vect(scene->cam->dir, scene->display.up));
}

void new_init_camera(t_scene *scene, t_ray *ray, float x, float y)
{
    t_scene *tmp_scene;
    t_vec3 coord;
    t_vec3 vertical;
    t_vec3 horizontal;
    t_vec3 res;

    tmp_scene = scene;
    ray->origin = new_vector(tmp_scene->cam->pos.x, tmp_scene->cam->pos.y, tmp_scene->cam->pos.z);
    coord.x = ((2.0f * x) / WIDTH) - 1;
    coord.y = ((2.0f * y) / HEIGHT) - 1;
    coord.z = 0;
    vertical = mult_vec3(scene->display.up, coord.y * scene->display.aspect_ratio);
    horizontal = mult_vec3(scene->display.right, coord.x * scene->display.scale);
    res = add_vec3(vertical, horizontal);
    res = add_vec3(res, scene->cam->dir);
    res = add_vec3(res, scene->cam->pos);
    ray->dir = sub_vec3(res, ray->origin);
    vec3D_normalize(&ray->dir);
}

int	render_scene(t_scene *scene)
{
	t_ray		ray;
	t_form_hit	hit;

	ft_memset(&hit, 0, sizeof(hit));
	ray.origin = scene->cam->pos;
	ray.dir.z = scene->cam->dir.z;
	init_camera(scene);
	for(int y = 0; y < scene->display.height; y++) {
		for (int x = 0; x < scene->display.width; x++) {
			new_init_camera(scene, &ray, x, y);
			//ray.dir.x = (2 * (x + 0.5) / (double) scene->display.width - 1) * scene->display.aspect_ratio * scene->display.scale;
            //ray.dir.y = (1 - 2 * (y + 0.5) / (double) scene->display.height) * scene->display.scale;
            //vec3D_normalize(&ray.dir);
			if (instersect_forms(scene, &ray, &hit))
			{
				scene->display.data[x + y * scene->display.width] =
					color_rgb(light_handler(scene, &ray, &hit));
			}
			else
				scene->display.data[x + y * scene->display.width] = 0;
		}
	}
	mlx_put_image_to_window(scene->display.mlx_ptr, scene->display.window,
		scene->display.render_img, 0, 0);
	fps_display(&scene->display);
	render_time_display(&scene->display);
	return (0);
}

// https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20ray
// tracing%20shapes.htm

/*

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

*/

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

t_u8b check_data(int n, int min, int max)
{
    if (n > max)
        return (max);
    else if (n < min)
        return (min);
    return (n);
}

t_rgb mult_color_vec4(t_rgb color, double b)
{
    t_rgb mult;

    mult.r = check_data(color.r * b, 0, 255);
    mult.g = check_data(color.g * b, 0, 255);
    mult.b = check_data(color.b * b, 0, 255);
    return (mult);
}

t_vec3 vec3_ambiant(t_rgb col, t_rgb color, float light_ratio)
{
    t_vec3 ambiant;

    ambiant.x = col.r * ((float) color.r / 255) * light_ratio;
    ambiant.y = col.g * ((float) color.g / 255) * light_ratio;
    ambiant.z = col.b * ((float) color.b / 255) * light_ratio;
    return (ambiant);
}

double vec3_length(t_vec3 vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

bool new_shadow_ray(t_scene *scene, t_form_hit *hit)
{
    double	light_distance;
    t_vec3	light_dir;
    t_ray	ray;

    vec3D_subtract(&scene->light->pos, &hit->hit, &light_dir);
    light_distance = vec3_length(light_dir);
    ray.origin = hit->hit;
    ray.dir = new_normalized(light_dir);
    return (intersect_light(scene, &ray, light_distance, hit));
}

t_rgb light_handler(t_scene *scene, t_ray *ray, t_form_hit *hit)
{
    t_rgb	final_color;
    t_rgb	color;
    double	d;
    t_vec3	diff_pos;

    // save ambiant lighting
    final_color = mult_color_vec4(*hit->color, scene->ambient->light_ratio);
    if (vec3D_dot(&hit->norm, &ray->dir) > 0)
    	vec3D_mult(&hit->norm, -1, &hit->norm);
    vec3D_subtract(&scene->light->pos, &hit->hit, &diff_pos);
    vec3D_normalize(&diff_pos);
    d = vec3D_dot(&hit->norm, &diff_pos);
    if (d < 0)
        d = 0;
    color = vect_to_rgb(vec3_ambiant(*hit->color, (t_rgb){255, 255, 255}, d * scene->light->brightness));
    if (new_shadow_ray(scene, hit) == true)
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

bool intersect_light(t_scene *scene, t_ray *ray, double light_distance,
	t_form_hit *hit)
{
    t_form_hit	tmp_hit;
    t_object	*obj;

    tmp_hit.t = INFINITY;
    obj = scene->objects;
    while (obj)
    {
        if (obj != hit->form)
        {
            if(instersect_forms(scene, ray, &tmp_hit) && tmp_hit.t < light_distance && tmp_hit.t > 0.0f)
                return (true);
        }
        obj = obj->next;
    }
    return (false);
}

t_rgb mult_rgb(t_rgb ambiant, double intensity)
{
    t_rgb new;
    new.r = check_data(ambiant.r * intensity, 0, 255);
    new.g = check_data(ambiant.g * intensity, 0, 255);
    new.b = check_data(ambiant.b * intensity, 0, 255);
    return (new);
}

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 added;

    added.x = a.x + b.x;
    added.y = a.y + b.y;
    added.z = a.z + b.z;
    return (added);
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
