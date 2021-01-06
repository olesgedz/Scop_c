/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:32:37 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:23:10 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "mesh.h"

void		model_bind_texture(t_model *model)
{
	if (model->texture.data)
	{
		model->shader->set_int(model->shader, "texture1", 0);
	}
}

void		model_modes_init(t_model *model)
{
	model->grey = 0;
	model->texture_exists = 0;
	model->color = 0;
	model->texture_mode = 0;
	model->smooth = 0;
}

t_model		*model_init(void)
{
	t_model *model;

	model = ft_memalloc_s(sizeof(t_model));
	model->texture.data = NULL;
	model->voa = -1;
	model->vbo_normals = -1;
	model->vbo_vertices = -1;
	model->temp_vertices = NULL;
	model->vertices = NULL;
	model->normals = NULL;
	model->shader = NULL;
	model_modes_init(model);
	return (model);
}
