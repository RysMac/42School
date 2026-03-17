/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:18:43 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:19:11 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framebuffer.h"
#include <stdlib.h>

int	fb_init(t_framebuffer *fb, size_t w, size_t h)
{
	fb->data = malloc(w * h * 3 * sizeof(uint8_t));
	if (!fb->data)
		return (1);
	fb->w = w;
	fb->h = h;
	return (0);
}

void	fb_free(t_framebuffer *fb)
{
	free(fb->data);
	fb->data = NULL;
}
