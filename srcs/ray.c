/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 12:38:33 by lgatibel          #+#    #+#             */
/*   Updated: 2016/11/17 14:39:32 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void				calc_ray(t_env *env, double x, double y)
{
			tp3d_cpy(&env->ray.dir,
			tp3d_sum(env->viewplane.upleft,
			tp3d_sub(
			tp3d_mult_nb(env->viewplane.rvec,x * env->xindent),
			tp3d_mult_nb(env->viewplane.upvec, y * env->yindent))));
			//facultatif ou necessaire
			if (env->ray.dir.z < 0)
				env->ray.dir.z = -env->ray.dir.z;
		//	normalized(&env->ray.dir);
}

void				set_ray(t_ray *ray)
{
	ray->pos.x = 0;
	ray->pos.y = 0;
	ray->pos.z = -1000;

	ray->dir.x = 0;
	ray->dir.y = 0;
	// a quoi cela sert
	ray->dir.z = 1;
}
