#include "../headers/minirt.h"

float	solve_quadratic(float a, float b, float c)
{
	return (-b - sqrt((b * b) - 4.0f * a * c) / (2.0f * a));
}

float	plane_equ(t_object *object, t_ray *ray)
{
	(void) object;
	(void) ray;
	return (0);
}

float	sphere_equ(t_object *sphere, t_ray *ray)
{
	float	a, b, c;
	t_vec3	newOrigin = {0, 0, 0};

	vec3D_subtract(&ray->origin, &sphere->pos, &newOrigin);
	a = vec3D_dot(&ray->dir, &ray->dir);
	b = 2.0f * vec3D_dot(&newOrigin, &ray->dir);
    c = vec3D_dot(&newOrigin, &newOrigin) - sphere->radius * sphere->radius;

	// quadratic formula discriminant
	// b² - 4ac
	return (solve_quadratic(a, b, c));
}

float	cylinder_equ(t_object *cy, t_ray *ray)
{
	t_vec3		u = {0, 0, 0};
	t_vec3		v = {0, 0, 0};
	double		a, b, c;

	vec3D_cross(&ray->dir, &cy->dir, &u);
	vec3D_subtract(&cy->pos, &ray->origin, &v);
	vec3D_cross(&v, &cy->dir, &v);
	a = vec3D_dot(&u, &u);
	b = 2 * vec3D_dot(&u, &v);
	c = vec3D_dot(&v, &v) - (cy->radius);

	double	delta = ((b * b) - 4.0f * a * c);
	double	t1;
	t_vec3	phit = {0, 0, 0};
	t_vec3	nhit = {0, 0, 0};

	/*a = ray->x * ray->x + ray->y * ray->y;
	b = 2.0f * cam_pos->pos.x * ray->x + 2.0f * cam_pos->pos.y * ray->y;
	c = cam_pos->pos.x * cam_pos->pos.x + cam_pos->pos.y * cam_pos->pos.y - 1000;*/
	if (delta > 0.0001f)
	{
		t1 = (-b + delta) / (2 * a);
		phit.x = ray->origin.x + t1 * ray->dir.x;
		phit.y = ray->origin.y + t1 * ray->dir.y;
		phit.z = ray->origin.z + t1 * ray->dir.z;
		vec3D_subtract(&phit, &ray->dir, &v);
		vec3D_cross(&v, &cy->dir, &nhit);
		vec3D_cross(&nhit, &cy->dir, &nhit);
		vec3D_normalize(&nhit);
		if (vec3D_dot(&nhit, &ray->dir))
		return (solve_quadratic(a, b, c));
	}
	return (0);
}

t_object	*instersect_forms(t_scene *scene, t_ray *ray)
{
	static float	(*equations[3])(t_object *, t_ray *) = {
		sphere_equ, plane_equ, cylinder_equ
	};
	t_object		*obj;
	t_object		*closest;
	float			closest_distance;
	float			distance;

	obj = scene->objects;
	closest_distance = 3.402823466e+38F;
	closest = NULL;
	while (obj)
	{
		distance = equations[obj->type](obj, ray);
		if (distance < 0.0f)
		{
			obj = obj->next;
			continue ;
		}
		if (distance < closest_distance)
		{
			closest_distance = distance;
			closest = obj;
		}

		obj = obj->next;
	}
	return (closest);
}

int	render_scene(t_scene *scene)
{
	t_ray		ray;
	float		scale;
	t_object	*closest;

	ray.origin = scene->cam->pos;
	ray.dir.z = scene->cam->dir.z;
	scale = 1.0f / tan((float) scene->cam->fov / 2);
	for(int y = 0; y < scene->display.height; y++) {
		for (int x = 0; x < scene->display.width; x++) {
			ray.dir.x = scale * (((2 * (x + 0.5) / (double) scene->display.width - 1) * scene->display.aspect_ratio));
            ray.dir.y = scale * (1 - 2 * (y + 0.5) / (double) scene->display.height);
			closest = instersect_forms(scene, &ray);
			if (closest)
			{
				scene->display.data[x + y * scene->display.width] =
					rgb_to_int(&closest->color, scene->display.big_endian);
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
