/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:30:55 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:42:38 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ugl.h"
#include "mesh.h"
#include "libft.h"

t_vec3	get_normal(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_vec3 temp1;
	t_vec3 temp2;
	t_vec3 normal;

	temp1 = ft_vec3_substract(v2, v1);
	temp2 = ft_vec3_substract(v3, v1);
	normal = ft_vec3_cross_multiply(temp1, temp2);
	normal = ft_vec3_normalize(normal);
	return (normal);
}

void	generate_normals(t_model *model, GLfloat *vertices)
{
	unsigned int			i;
	unsigned int			t;
	t_vec3					temp;

	t = 0;
	i = 0;
	model->num_normals = model->num_indices * 3;
	while (i < model->num_vertices)
	{
		temp = get_normal((t_vec3){vertices[i], vertices[i + 1],
		vertices[i + 2]},
		(t_vec3){vertices[i + 3], vertices[i + 4], vertices[i + 5]},
		(t_vec3){vertices[i + 6], vertices[i + 7], vertices[i + 8]});
		t = -1;
		while (++t < 3)
		{
			model->normals[i + 3 * t] = temp.x;
			model->normals[i + 1 + 3 * t] = temp.y;
			model->normals[i + 2 + 3 * t] = temp.z;
		}
		i += 9;
	}
}

void	load_obj_fill(t_model *model, int v, int f)
{
	model->size_vertices = v * sizeof(GLfloat);
	model->size_indices = f * sizeof(GLuint);
	model->num_indices = f;
	model->num_vertices = v;
	model->center = ft_vec3_neg(center_axis(model->temp_vertices,
	model->num_vertices));
	model->vertices = ft_memalloc_s(sizeof(float) * model->num_indices * 3);
}

void	load_obj_fill2(t_model *model)
{
	unsigned int i;
	unsigned int t;

	i = 0;
	t = 0;
	while (i < model->num_indices)
	{
		model->vertices[t] = model->temp_vertices[model->indices[i] * 3 + 0];
		model->vertices[t + 1] = model->temp_vertices[
		model->indices[i] * 3 + 1];
		model->vertices[t + 2] = model->temp_vertices[
		model->indices[i] * 3 + 2];
		i++;
		t += 3;
	}
	model->num_vertices = model->num_indices * 3;
	model->normals = ft_memalloc(sizeof(float) * model->num_indices * 3);
	generate_normals(model, model->vertices);
}

void	load_obj(t_model *model, char *filename)
{
	int		fd;
	int		v;
	int		f;
	char	*line;

	v = 0;
	f = 0;
	model->temp_vertices = (GLfloat*)ft_memalloc(sizeof(GLfloat) * 3);
	model->indices = (GLuint*)ft_memalloc(sizeof(GLuint) * 3);
	if ((fd = open(filename, O_RDWR)) == -1)
		ft_terminate("obj file opening failed.");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			model->temp_vertices = add_vertices(model->temp_vertices,
			line, &v);
		}
		else if (line[0] == 'f' && line[1] == ' ')
			model->indices = add_indices(model->indices, line, &f);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	load_obj_fill(model, v, f);
	load_obj_fill2(model);
}
