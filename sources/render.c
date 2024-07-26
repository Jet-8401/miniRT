#include "../headers/minirt.h"

/*
red = (uint8_t)((x / (float) display->width) * 255);
green = (uint8_t)((y / (float) display->height) * 255);
display->data[x + y * display->width] = red << 16 | green << 8;
*/

int	render_scene(t_scene *scene)
{
	//static uint32_t	red;
	//static uint32_t	green;
	static t_vec3	ray;
	float			a;
	float			b;
	float			c;
	float			scale;

	ray.z = 1;
	scale = tan((float) scene->cam->fov / 2);
	for(int y = 0; y < scene->display.height; y++) {
		for (int x = 0; x < scene->display.width; x++) {
			// for now the sphere only work when centered in 0 0 0
			// coordinates are not at the scale of fov
			ray.x = (2 * (x + 0.5) / (double) scene->display.width - 1) * scene->display.aspect_ratio * scale;
            ray.y = (1 - 2 * (y + 0.5) / (double) scene->display.height) * scale;
            //printf("x=%f\ny=%f\n", coords.x, coords.y);
            vec3D_normalize(&ray);
            // a ray origin
            // b ray direction
            // r radius
            // t hit distance
            // quadratic formula:
            // (b²)t² + (2 * (a*b))t + (a² - r²) = 0
            a = vec3D_dot(&ray, &ray);
            b = 2.0f * vec3D_dot(&scene->cam->pos, &ray);
            c = vec3D_dot(&scene->cam->pos, &scene->cam->pos)
            	- (scene->sphere->diameter * scene->sphere->diameter);
            // quadratic formula discriminant
            // b² - 4ac
            if (((b * b) - 4.0f * a * c) > 0.0f)
            {
            	scene->display.data[x + y * scene->display.width] = 255 << 16;
             	continue;
            }
            scene->display.data[x + y * scene->display.width] = 0;
		}
	}
	(void) ray;
	mlx_put_image_to_window(scene->display.mlx_ptr, scene->display.window,
		scene->display.render_img, 0, 0);
	fps_display(&scene->display);
	return (0);
}
