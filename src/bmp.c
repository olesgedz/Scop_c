/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:11:56 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 23:14:04 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "libft.h"

unsigned char	*parse_bmp(char const *pathname, int *width, int *height)
{
	FILE				*file;
	t_bmp_header		header;
	t_bmp_dib_header	dib_header;
	unsigned char		*data;
	unsigned			size_read;

	file = fopen(pathname, "r+b");
	if (file == NULL)
		ft_terminate("error\n");
	if (fread(&header, 1, sizeof(t_bmp_header), file) != sizeof(t_bmp_header))
		ft_terminate("error\n");
	if (header.data_offset > header.data_offset)
		ft_terminate("error\n");
	if (fread(&dib_header, 1, sizeof(dib_header), file) != sizeof(dib_header))
		ft_terminate("error\n");
	*width = dib_header.image_width;
	*height = dib_header.image_height;
	fseek(file, header.data_offset, SEEK_SET);
	data = (unsigned char*)calloc(dib_header.image_size, sizeof(unsigned char));
	size_read = fread(data, 1, dib_header.image_size, file);
	if (size_read != dib_header.image_size)
		ft_terminate("error\n");
	return (data);
}
