#include "../headers/minirt.h"

// quadratic formula
// -b - sqrt((b * b) - 4.0f * a * c) / (2.0f * a)

float	solve_quadratic(float a, float b, float c)
{
	return (-b - sqrt((b * b) - 4.0f * a * c) / (2.0f * a));
}

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

    /*vec3D_mult(&ray->dir, hit->t, &hit->hit);
    vec3D_add(&ray->origin, &hit->hit, &hit->hit);
    vec3D_subtract(&hit->hit, &sphere->pos, &hit->norm);
    vec3D_normalize(&hit->norm);*/
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

bool	intercept_object(t_object *object, t_ray *ray, t_form_hit *hit)
{
	static bool	(*equations[3])(t_object *, t_ray *, t_form_hit *) = {
		sphere_equ, plane_equ, cylinder_equ
	};

	return (equations[object->type](object, ray, hit));
}

bool	instersect_forms(t_scene *scene, t_ray *ray, t_form_hit *hit)
{
	t_object		*obj;
	float			closest_distance;
	bool			has_hit;

	obj = scene->objects;
	closest_distance = 3.402823466e+38F;
	has_hit = 0;
	while (obj)
	{
		if (intercept_object(obj, ray, hit) && hit->t < closest_distance)
		{
			has_hit = 1;
			closest_distance = hit->t;
			hit->form = obj;
		}
		obj = obj->next;
	}
	return (has_hit);
}

int	render_scene(t_scene *scene)
{
	t_ray		ray;
	t_form_hit	hit;

	ray.origin = scene->cam->pos;
	ray.dir.z = scene->cam->dir.z;
	ft_memset(&hit, 0, sizeof(hit));
	for(int y = 0; y < scene->display.height; y++) {
		for (int x = 0; x < scene->display.width; x++) {
			ray.dir.x = 2 * (x + 0.5) / (double) scene->display.width - 1;
            ray.dir.y = 1 - 2 * (y + 0.5) / (double) scene->display.height;
			if (instersect_forms(scene, &ray, &hit))
			{
				scene->display.data[x + y * scene->display.width] =
					rgb_to_int(&hit.form->color, scene->display.big_endian);
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
