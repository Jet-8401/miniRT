#include "../headers/minirt.h"

void	render_time_display(t_display *display)
{
	static uint64_t	previous_snapshot;
	uint64_t		new_snapshot;

	new_snapshot = get_time();
	mlx_string_put(display->mlx_ptr, display->window, 0, 22, STRING_COLOR,
		ft_itoa(new_snapshot - previous_snapshot));
	previous_snapshot = new_snapshot;
}
