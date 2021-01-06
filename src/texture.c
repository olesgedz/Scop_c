/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:31:41 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:19:05 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "mesh.h"

void	read_header(char *filename, t_model *model)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
		ft_terminate("bmp file opening (fopen) failed.");
	fseek(file, 18, SEEK_SET);
	fread(&model->texture.width, 4, 1, file);
	fread(&model->texture.height, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&model->texture.bpp, 2, 1, file);
	fclose(file);
	model->texture.oop = model->texture.bpp / 8;
	model->texture.sl = model->texture.width * model->texture.oop;
	model->texture.width < 0 ? model->texture.width = -model->texture.width : 0;
	model->texture.height < 0 ? model->texture.height =
	-model->texture.height : 0;
	model->texture.size = model->texture.sl * model->texture.height;
}

void	get_image(t_texture *texture, char *buffer, int i)
{
	int	h;
	int	j;
	int	size;

	h = 0;
	size = texture->size * 2;
	texture->data = (unsigned char*)ft_memalloc_s(sizeof(unsigned char) * size);
	while (i >= 0)
	{
		i -= texture->sl;
		j = 0;
		while (j < texture->sl)
		{
			texture->data[i + j] = (unsigned char)buffer[i + j + 2];
			texture->data[i + j + 1] = (unsigned char)buffer[i + j + 1];
			texture->data[i + j + 2] = (unsigned char)buffer[i + j];
			j += 3;
		}
		h += texture->sl;
	}
}

t_mat4	set_projection_matrix(void)
{
	float		s;
	float		far;
	float		near;
	float		fov;
	t_mat4		ret;

	fov = 70.f;
	ret = ft_mat4_zero();
	far = 100.f;
	near = 0.1f;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	ret = ft_mat4_identity_matrix();
	ret.matrix[0][0] = s / ((float)SCR_WIDTH / (float)SCR_HEIGHT);
	ret.matrix[1][1] = s;
	ret.matrix[2][2] = -(far + near) / (far - near);
	ret.matrix[2][3] = -1;
	ret.matrix[3][2] = -2 * far * near / (far - near);
	return (ret);
}

void	load_texture(t_model *model, char *filename)
{
	if (filename)
	{
		model->texture.data = parse_bmp(filename,
		&model->texture.width, &model->texture.height);
		if (model->texture.data)
		{
			glGenTextures(1, &model->texture.id);
			glBindTexture(GL_TEXTURE_2D, model->texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model->texture.width,
	model->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, model->texture.data);
			glGenerateMipmap(GL_TEXTURE_2D);
			model->texture_exists = 1;
		}
		else
			ft_putstr("Failed to parsing texture\n");
	}
	else
		ft_putstr("Failed to load texture\n");
}
