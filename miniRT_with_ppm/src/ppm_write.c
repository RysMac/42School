/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:47:35 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:48:20 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>    // fopen, fprintf, fwrite, fclose
#include <stdint.h>   // uint8_t
#include "framebuffer.h"

// Header: P6 + width height + maxval 255 + newline after 255
int	ppm_write(const char *path, const t_framebuffer *fb)
{
	size_t	total;
	size_t	n;
	FILE	*f;

	if (!path || !fb || !fb->data || fb->w == 0 || fb->h == 0)
		return (1);
	f = fopen(path, "wb");
	if (!f)
		return (1);
	if (fprintf(f, "P6\n%zu %zu\n255\n", fb->w, fb->h) < 0)
	{
		fclose(f);
		return (1);
	}
	total = fb->w * fb->h * 3;
	n = fwrite(fb->data, 1, total, f);
	if (n != total)
	{
		fclose(f);
		return (1);
	}
	if (fclose(f) != 0)
		return (1);
	return (0);
}
