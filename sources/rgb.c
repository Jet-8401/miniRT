#include "../headers/minirt.h"

int	rgb_to_int(t_rgb *rgb, t_u8b is_big_endian)
{
	if (is_big_endian)
		return ((rgb->r << 24) | (rgb->g << 16) | (rgb->b << 8));
	else
		return ((rgb->r << 16) | (rgb->g << 8) | rgb->b);
}
