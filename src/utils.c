/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:33:17 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:41:31 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			check_params(int argc, char **argv)
{
	if (argc == 1)
		ft_terminate("usage: model.obj [texture.bmp]\n");
	if (argc == 2)
	{
		if (!strcmpend(argv[1], ".obj"))
			ft_terminate("wrong model file type\n");
	}
	if (argc == 3)
	{
		if (!strcmpend(argv[2], ".bmp"))
			ft_terminate("wrong texture type\n");
	}
	return (1);
}

int			strcmpend(char *heap, char *needle)
{
	int len1;
	int len2;

	if (!heap || !needle)
		return (0);
	len1 = ft_strlen(heap);
	len2 = ft_strlen(needle);
	if (len1 < len2)
		return (0);
	while (0 <= len2)
	{
		if (heap[len1] != needle[len2])
		{
			return (0);
		}
		len1--;
		len2--;
	}
	return (1);
}

void		update_time(t_scene *scene)
{
	scene->current_frame = glfwGetTime();
	scene->delta = scene->current_frame - scene->last_time;
	scene->last_time = scene->current_frame;
}

void		key_switch(int *key)
{
	if (*key == 0)
		*key = 1;
	else if (*key == 1)
		*key = 0;
	else
		*key = 0;
}
