/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:30:55 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 23:29:05 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ugl.h"
#include "mesh.h"
#include "libft.h"

int		array_len(void **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

GLuint	*gluint_array_copy(GLuint *array, int length, int m)
{
	int		i;
	GLuint	*new;

	i = -1;
	new = (GLuint*)malloc(sizeof(GLuint) * length);
	while (++i < length - m)
		new[i] = array[i];
	free(array);
	array = new;
	return (new);
}


GLfloat	*append_vertices(GLfloat *array, char *line, int *length)
{
	int		i;
	int		j;
	char	**tab;
	GLfloat	*new;

	tab = ft_strsplit(&line[1], ' ');
	*length += 3;
	new = (GLfloat*)ft_memalloc(sizeof(GLfloat) * *length);
	i = -1;
	while (++i < *length - 3)
		new[i] = array[i];
	free(array);
	array = new;
	j = -1;
	while (tab[++j] != NULL)
	{
		array[*length - 3 + j] = (GLfloat)ft_atof(tab[j]);
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	ft_memdel((void *)&tab);
	return (array);
}

GLuint	*append_indices(GLuint *array, char *line, int *length)
{
	int		j;
	int		l;
	char	**tab;

	tab = ft_strsplit(&line[1], ' ');
	l = array_len((void**)tab) == 4 ? 6 : 3;
	*length += l;
	array = gluint_array_copy(array, *length, l);
	j = -1;
	while (++j < 3)
	{
		array[*length - l + j] = (GLuint)ft_atoi(tab[j]) - 1;
		if (l == 6)
			array[*length - l + 3 + j] =
			(GLuint)ft_atoi(tab[j > 0 ? j + 1 : 0]) - 1;
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	ft_memdel((void *)&tab);
	return (array);
}


t_vec3	compute_center_axis(GLfloat *vertices, int num_vertices)
{
	int		i;
	t_vec3	max;
	t_vec3	min;
	t_vec3	center;

	i = 0;
	max = (t_vec3){0, 0, 0};
	min = (t_vec3){0, 0, 0};
	while (i < num_vertices - 6)
	{
		vertices[i] > max.x ? max.x = vertices[i] : 0;
		vertices[i] < min.x ? min.x = vertices[i] : 0;
		vertices[i + 1] > max.y ? max.y = vertices[i + 1] : 0;
		vertices[i + 1] < min.y ? min.y = vertices[i + 1] : 0;
		vertices[i + 2] > max.z ? max.z = vertices[i + 2] : 0;
		vertices[i + 2] < min.z ? min.z = vertices[i + 2] : 0;
		i += 6;
	}
	center = ft_vec3_scalar_multiply(ft_vec3_sum(max, min), 0.5);
	return (center);
}
t_vec3 get_normal(t_vec3 v1, t_vec3 v2, t_vec3 v3)
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

void generate_normals(t_model *model, GLfloat *vertices)
{
	int 	i;
	int 	t;
	t_vec3 	temp;

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
	model->center = ft_vec3_neg(compute_center_axis(model->temp_vertices,
	model->num_vertices));
	model->vertices = ft_memalloc_s(sizeof(float) * model->num_indices * 3);
}

void	load_obj_fill2(t_model *model)
{
	int i;
	int t;

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
			model->temp_vertices = append_vertices(model->temp_vertices,
			line, &v);
		}
		else if (line[0] == 'f' && line[1] == ' ')
			model->indices = append_indices(model->indices, line, &f);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	load_obj_fill(model, v, f);
	load_obj_fill2(model);
}