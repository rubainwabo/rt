/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:57:28 by krutten           #+#    #+#             */
/*   Updated: 2019/12/19 22:37:12 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include "../includes/minilibx/mlx.h"
# include "../includes/libft/libft.h"
# include "key.h"
# define THREAD_COUNT 64
# define FAR 1000000
# define NEAR 0.0002
# define MAX_DEPTH 10
# define WIDTH 1200
# define HEIGHT 800
# define W_IMG 900
# define H_IMG 800
# define POS_X 300
# define POS_Y 0
# define BLACK 0x0
# define WHITE 0xffffff
# define BLUE 0x0000ff
# define GREEN 0x00ff00
# define RED 0xff0000
# define FAIL -100

typedef struct		s_surf
{
	t_vec3			d_col;
	float			d_k;
	t_vec3			s_col;
	int				s_exp;
	float			s_k;
	float			ior;
	int				type;
}					t_surf;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direct;
	t_vec3			colour;
	double			t;
	t_vec3			hitpoint;
	t_vec3			hitnormal;
	t_surf			*surf;
	int				depth;
	float			ior;
	int				nohit;
}					t_ray;

typedef struct		s_obj
{
	void			*obj;
	int				id;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_image
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				height;
	int				width;
}					t_image;

typedef struct		s_rt
{
	char			*file_name;
	int				w_img;
	int				h_img;
	short			event;
	void			*mlx;
	void			*win;
	void			*img;
	void			*img2;
	int				bpp;
	int				size_line;
	int				size_line2;
	int				endian;
	t_vec3			camera;
	t_vec3			view_dir;
	t_image			*textures[6];
	double			fov;
	t_mat3			view_rot;
	double			alpha;
	double			aspect;
	char			**input;
	char			*img_str;
	char			*img_str2;
	t_obj			*obj_list;
	t_obj			*light_list;
	int				(*fct_ptr[4])(struct s_rt *specs, t_ray *, void *);
	int				x;
	int				y;
	int				far_col;
	int				nb_line;
	char			*str;
	void			*cache;
	int				cache_id;
	int				first;
}					t_rt;

typedef struct		s_thread
{
	t_rt			*specs;
	int				y_start;
	int				y_end;
}					t_thread;

typedef struct		s_light_s
{
	t_vec3			center;
	t_vec3			color;
	double			intensity;
}					t_light_s;

typedef struct		s_light_d
{
	t_vec3			direct;
	t_vec3			color;
	double			intensity;
}					t_light_d;

typedef struct		s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_surf			*surf;
}					t_plane;

typedef struct		s_sphere
{
	t_vec3			center;
	double			radius;
	t_surf			*surf;
}					t_sphere;

typedef struct		s_cone
{
	t_vec3			center;
	t_vec3			axis;
	double			min;
	double			max;
	double			angle;
	t_surf			*surf;
}					t_cone;

typedef struct		s_cyl
{
	t_vec3			center;
	t_vec3			axis;
	double			max;
	double			radius;
	t_surf			*surf;
}					t_cyl;

/*
** NORME STRUCT
*/

typedef struct		s_var
{
	t_vec3			oc;
	double			t;
	t_plane			p;
	double			dist;
	double			rad;
	int				red;
	int				green;
	int				blue;
	double			a;
	double			b;
	double			c;
	double			d;
	double			t1;
	double			t2;
	t_sphere		*s;
	t_cyl			*cyl;
	t_cone			*cone;
	t_plane			*plane;
	t_sphere		*sphere;
	t_vec3			ext;
	int				pix[4];
	int				coord[17];
}					t_var;

/*
** PARSING
*/

void				parse(t_rt *specs);
char				*move(int *i, int *j, t_rt *specs);
void				starter(int *i, int *j, t_rt *specs);
void				parse_objects(int *i, t_rt *specs);
t_obj				*new_object(void *inf, int id);
void				add_object(t_obj **list, t_obj *new);
void				free_all_lists(t_rt *specs);
void				free_array(char **array, int index, t_rt *specs,
							char *line);
void				exit_protocol(t_rt *specs, int p, char *err);
void				exit_protocol2(t_rt *specs, int p, char *err);
void				parse_vec(t_vec3 *ptr, char *input, t_rt *specs);
void				parse_vec_norm(t_vec3 *ptr, char *input, t_rt *specs);
void				parse_vec_col(t_vec3 *ptr, char *input, t_rt *specs);
t_surf				*set_surface(t_rt *specs);
void				free_surface(int id, void *ptr);
void				parse_lights_s(int *i, t_rt *specs);
void				parse_lights_d(int *i, t_rt *specs);

/*
** RENDERING
*/

int					sphere_intersect(t_rt *specs, t_ray *ray, void *hit_object);
int					plane_intersect(t_rt *specs, t_ray *ray, void *hit_object);
int					cone_intersect(t_rt *specs, t_ray *ray, void *hit_object);
int					deal_mouse(int button, int x, int y, void *param);
int					deal_key(int key, t_rt *specs);
int					cylinder_intersect(t_rt *specs, t_ray *ray, void *hit_object);
t_mat3				rot_from_base(t_vec3 view, t_vec3 base, int wrong);
t_vec3				normalise(t_vec3 v1);
void				loop_ray_over_objects(t_ray *ray, t_rt *specs);
void				loop_shadow_ray_over_objects(t_ray *ray, t_rt *specs);
void				lighting(t_ray *ray, t_rt *specs);
void				intersection_vec3(t_ray *ray);
t_vec3				pixel_to_world(float x, float y, t_rt *specs);
int					cap_intersect_top(t_ray *ray, t_cyl *specs);
int					cap_intersect_bot(t_ray *ray, t_cyl *specs);
int					cone_cap_intersect_bot(t_ray *ray, t_cone *specs);
int					cone_cap_intersect_top(t_ray *ray, t_cone *specs);
int					draw_image(t_rt *specs);
void				normal_towards_cam(t_ray *ray);
void				*pixel_loop(void *data);
int					solve_polynom_2(double *abc, double *t1, double *t2);
t_mat3				mat3_scale(t_mat3 a, double c);
t_vec3				reflect(t_vec3 norm, t_vec3 inci);
void				reflected_ray(t_ray *ray, t_ray *refl);
void				refracted_ray(t_ray *ray, t_ray *refr);
void				launch_threads(t_rt *specs, int n);
void				fresnel_blend(t_ray *refl, t_ray *refr, t_ray *ray);
int					init_rt_struct(int fd, t_rt *new, char **av);
int					colour_mask(float att, t_vec3 col, t_ray *ray);
int					diffuse_prot(t_ray *ray, t_rt *specs, t_ray *original);
void				shading(t_ray *ray, t_rt *specs, int x, int y);
void				shading_far(t_rt *specs, int x, int y);
t_vec3				apply_texture(t_rt *specs, t_vec3 direct);
int					move_cam(int button, int x, int y, t_rt *specs);
void				draw_backgrd(t_rt *specs);
void				possible_events(t_rt *specs);
void				possible_events2(t_rt *specs);
void				save_file(t_rt *specs);

#endif
