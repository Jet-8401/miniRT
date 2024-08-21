#include "../headers/minirt.h"
#include <math.h>

/*
red = (uint8_t)((x / (float) display->width) * 255);
green = (uint8_t)((y / (float) display->height) * 255);
display->data[x + y * display->width] = red << 16 | green << 8;
*/

t_rgb	*plane_equ(struct s_cam *cam_pos, void *object, t_vec3 *ray)
{
	(void) cam_pos;
	(void) object;
	(void) ray;
	return (0);
}

t_rgb	*sphere_equ(struct s_cam *cam_pos, void *sphere, t_vec3 *ray)
{
	float	a, b, c;

	a = vec3D_dot(ray, ray);
	b = 2.0f * vec3D_dot(&cam_pos->pos, ray);
    c = vec3D_dot(&cam_pos->pos, &cam_pos->pos) -
    	(((t_sphere *) sphere)->radius) * (((t_sphere *) sphere)->radius);

	// quadratic formula discriminant
	// b² - 4ac
	if (((b * b) - 4.0f * a * c) > 0.0f)
		return (&((t_sphere *) sphere)->color);
	return (NULL);
}

t_rgb	*cylinder_equ(struct s_cam *cam_pos, void *object, t_vec3 *ray)
{
	float		a, b, c;
	t_cylinder	*cy = (t_cylinder *) object;

	(void) cam_pos;
	a = cy->pos.x * cy->pos.x + cy->pos.y * cy->pos.y;
	b = 2.0 * (ray->x * cy->pos.x + ray->y * cy->pos.y);
	c = ray->x * ray->x + ray->y * ray->y - ((cy->diameter / 2) * (cy->diameter / 2));

	double numSQRT = sqrt((b * b) - 4.0f * a * c);
	if (numSQRT > 0.0f)
		return (&cy->color);
	return (NULL);
}

t_rgb	*instersect_form(t_scene *scene, t_vec3 *ray)
{
	void	*objects[4] = { scene->plane, scene->sphere, scene->cylinder, NULL };
	t_rgb	*(*equation[4])(struct s_cam *, void *, t_vec3 *) = {
		&plane_equ, &sphere_equ, &cylinder_equ };
	int		i;
	t_rgb	*color;

	i = -1;
	while (objects[++i])
	{
		color = (equation[i])(scene->cam, objects[i], ray);
		if (color)
			return (color);
	}
	return (NULL);
}

int	render_scene(t_scene *scene)
{
	t_vec3	ray;
	float	scale;
	t_rgb	*color;

	ray.z = scene->cam->dir.z;
	scale = 1.0f / tan((float) scene->cam->fov / 2);
	for(int y = 0; y < scene->display.height; y++) {
		for (int x = 0; x < scene->display.width; x++) {
			ray.x = ((2 * (x + 0.5) / (double) scene->display.width - 1) * scene->display.aspect_ratio) * scale;
            ray.y = (1 - 2 * (y + 0.5) / (double) scene->display.height) * scale;
			color = instersect_form(scene, &ray);
			if (color)
				scene->display.data[x + y * scene->display.width] =
					rgb_to_int(color, scene->display.big_endian);
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
