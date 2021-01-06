/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:48:38 by olesgedz          #+#    #+#             */
/*   Updated: 2021/01/06 15:50:58 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include "stb_image.h"
# include "ugl.h"
# include "shader.h"
# include "mesh.h"
# include "scene.h"
# define SCR_WIDTH 800
# define SCR_HEIGHT 600

typedef struct	s_mouse
{
	int			first_mouse;
	int			last_x;
	int			last_y;
	int			cursor;
}				t_mouse;
void			mouse_callback(GLFWwindow *window, double xpos, double ypos);
void			framebuffer_size_callback(GLFWwindow *window,\
int width, int height);
void			process_input(GLFWwindow *window);
t_scene			*scene_create();
t_scene			*scene_init(t_scene *scene, t_gl *gl, t_model *model);
void			read_header(char *filename, t_model *model);
void			get_image(t_texture *texture, char *buffer, int i);
t_mat4			set_projection_matrix();
void			load_texture(t_model *model, char *filename);
void			model_bind_texture(t_model *model);
t_model			*model_init(void);
void			upload_texture(t_model *model);
void 			upload_model(t_model *model);
void 			renderer(t_gl *gl, t_model *model, t_scene *scene);
int				check_params(int argc, char **argv);
int				strcmpend(char *heap, char *needle);
void			update_time(t_scene *scene);
void			key_switch(int *key);
#endif