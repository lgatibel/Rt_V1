/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:25:38 by lgatibel          #+#    #+#             */
/*   Updated: 2016/12/12 13:42:47 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void			set_mlx(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "hello");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->bpp = 0;
	env->size_line = 0;
	env->endian = 0;
	env->img_addr = (int *)mlx_get_data_addr(env->img,
	&env->bpp, &env->size_line, &env->endian);
}

void				set_env(t_env *env)
{
	env->final_color = 0;
	env->object = NULL;
	env->xindent = 0;
	env->yindent = 0;
	env->color = BLACK;
	env->bpp = 0;
	env->size_line = 0;
	env->endian = 0;
	set_mlx(env);
	env->line = NULL;
	env->t = -1;
	env->i = 0;
}

void				set_viewplane(t_env *env)
{
	t_viewplane		*view;
	t_p3d			vecdir;

	view = &env->viewplane;
	view->dist = 1;
	view->width = VIEW_WIDTH;
	view->height = VIEW_HEIGHT;
	set_tp3d(&vecdir, 0, 0, 1);
	set_tp3d(&view->upvec, 0, 1, 0);
	set_tp3d(&view->rvec, 1, 0, 0);
	view->upleft = sub_tp3d(
	sum_tp3d(
	sum_tp3d(env->cam.pos, mult_nb_tp3d(vecdir,//env->cam.rot,
	view->dist)), mult_nb_tp3d(view->upvec, view->height /
	2.0f)), mult_nb_tp3d(view->rvec, view->width / 2.0f));
	env->xindent = view->width / WIDTH;
	env->yindent = view->height / HEIGHT;
}
