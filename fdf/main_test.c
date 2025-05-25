#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH  3
#define HEIGHT 3

typedef struct s_point
{
	int x;
	int y;
	int z;
	int screen_x;
	int screen_y;
}	t_point;

// void project_point(t_point *p, int scale, int height_scale)
// {
// 	double angle = M_PI / 6; // 30 degrees in radians

// 	double iso_x = (p->x - p->y) * cos(angle) * scale;
// 	double iso_y = (p->x + p->y) * sin(angle) * scale - p->z * height_scale;

// 	p->screen_x = iso_x + 250;
// 	p->screen_y = iso_y + 250;
// }

void project_point(t_point *p, int scale, int height_scale)
{
	int iso_x = (p->x - p->y) * scale;
	int iso_y = (p->x + p->y) * scale / 2 - p->z * height_scale;

	p->screen_x = iso_x + 250;
	p->screen_y = iso_y + 250;
}

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x0 += sx; }
		if (e2 < dx)  { err += dx; y0 += sy; }
	}
}

#define ESC_KEY 65307  // On Linux with X11. Use 53 on macOS.

int handle_keypress(int keycode, void *param)
{
	if (keycode == ESC_KEY)
	{
		printf("ESC pressed. Exiting.\n");
		exit(0);  // or cleanup and then exit
	}
	return (0);
}

int main(void)
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 500, 500, "FDF Test");

	int heights[HEIGHT][WIDTH] = {
		{0, 1, 0},
		{1, 2, 1},
		{0, 1, 0}
	};

	t_point grid[HEIGHT][WIDTH];

	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			grid[y][x].x = x;
			grid[y][x].y = y;
			grid[y][x].z = heights[y][x];
			project_point(&grid[y][x], 30, 1);
			x++;
		}
		y++;
	}

	// draw horizontal lines
	y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH - 1)
		{
			draw_line(mlx, win,
				grid[y][x].screen_x, grid[y][x].screen_y,
				grid[y][x + 1].screen_x, grid[y][x + 1].screen_y);
			x++;
		}
		y++;
	}

	// draw vertical lines
	int x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT - 1)
		{
			draw_line(mlx, win,
				grid[y][x].screen_x, grid[y][x].screen_y,
				grid[y + 1][x].screen_x, grid[y + 1][x].screen_y);
			y++;
		}
		x++;
	}

	mlx_key_hook(win, handle_keypress, NULL);
	mlx_loop(mlx);
	return 0;
}
