/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:30:55 by jblack-b          #+#    #+#             */
/*   Updated: 2020/03/07 17:23:43 by jblack-b         ###   ########.fr       */
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
	// printf("%s\n", line);
	tab = ft_strsplit(&line[1], ' ');
	*length += 3;
	new = (GLfloat*)malloc(sizeof(GLfloat) * *length);
	i = -1;
	while (++i < *length - 3)
		new[i] = array[i];
	free(array);
	array = new;
	j = -1;
	printf("%s\n", line);
	// int l = 0;
	// while(tab[l])
	// {
	// 	printf("%s\n", tab[l]);
	// 	l+=1;
	// }
	while (tab[++j] != NULL)
	{
		array[*length - 3 + j] = (GLfloat)ft_atof(tab[j]);
		// printf("%f %f\n", array[*length - 6 + j], array[*length - 3 + j]);
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	free(tab);
	tab = NULL;
	return (array);
}

GLuint	*append_indices(GLuint *array, char *line, int *length)
{
	int		j;
	int		m;
	char	**tab;

	tab = ft_strsplit(&line[1], ' ');
	m = array_len((void**)tab) == 4 ? 6 : 3;
	*length += m;
	array = gluint_array_copy(array, *length, m);
	j = -1;
	while (++j < 3)
	{
		array[*length - m + j] = (GLuint)ft_atoi(tab[j]) - 1;
		if (m == 6)
			array[*length - m + 3 + j] =
			(GLuint)ft_atoi(tab[j > 0 ? j + 1 : 0]) - 1;
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	free(tab);
	tab = NULL;
	return (array);
}


void	load_obj(t_model *model, char *filename)
{
	int		fd;
	int		v;
	int		f;
	char	*line;

	v = 0;
	f = 0;
	model->vertices = (GLfloat*)ft_memalloc(sizeof(GLfloat) * 3);
	model->indices = (GLuint*)ft_memalloc(sizeof(GLuint) * 3);
	if ((fd = open(filename, O_RDWR)) == -1)
		ft_terminate("obj file opening failed.");
	// int i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			model->vertices = append_vertices(model->vertices, line, &v);
			// i++;
		}
		else if (line[0] == 'f' && line[1] == ' ')
			model->indices = append_indices(model->indices, line, &f);
		ft_strdel(&line);
	}
	// printf("vVVVVV->%d\n", i);
	ft_strdel(&line);
	model->size_vertices = v * sizeof(GLfloat);
	model->size_indices = f * sizeof(GLuint);
	model->num_indices = f;
    model->num_vertices = v;
	// e->model.center_axis = compute_center_axis(e->model.vertices, v);
	// center_vertices(e, v);
}