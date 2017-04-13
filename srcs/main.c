/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:19:35 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/09 17:17:54 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_object			*calc_object(t_object *object, t_ray *ray)
{
	double		t;
	t_object	*nearest;

	t = -1;

	nearest = NULL;
	while (object)
	{
		if (object->type == SPHERE)
			t = calc_sphere(object, ray);
		else if (object->type == CYLINDER)
			t = calc_cylinder(object, ray);
		else if (object->type == CONE)
			t  = calc_cone(object, ray);
		else if (object->type == PLANE)
			t = calc_plane(object, ray);
		object->dist = length_ray(ray, t, object);
		if (object->dist >= 0 && ((!nearest) || (object->dist < nearest->dist)))
			nearest = object;
		object = object->next;
	}
	return (nearest);
}

t_p3d				calc_normal(t_p3d *intersect, t_object *object)
{
	if (object->type == SPHERE)
		return(calc_sphere_normal(intersect, object));
	else if (object->type == CYLINDER)
		return (calc_cylinder_normal(intersect, object));
	else if (object->type == CONE)
		return (calc_cone_normal(object));
	else if (object->type == PLANE)
		return (calc_plane_normal(object));
	else
		set_tp3d(&object->normal, -8, -8, -8);
	return (object->normal);
}

int					calc_light(t_env *env)
{
	t_ray		*light;
	double		angle;
	double		diffuse;
	int			col;
	t_object	*nearest;
	t_p3d		normal;

//	printf("inter.x[%f], set[%d]\n",env->nearest_object->inter.y,
//	env->nearest_object->set);
	nearest = NULL;
	light = &env->light;
	light->dir = sub_tp3d(env->nearest_object->inter, light->pos);
	normalized(&light->dir);
	if (!(nearest = calc_object(env->object, light)) || env->nearest_object != nearest)
	{
		return (FONT);
	}





	reverse_tp3d(&light->dir);
//	nearest = env->nearest_object;
	env->color = env->nearest_object->color;

	normal = calc_normal(&nearest->inter, nearest);
	normalized(&normal);


	angle = dot_product_tp3d(normal, light->dir);
	diffuse = (angle > 0) ? angle * COEFF : 0;
	// diffuse = (angle > 0) ? angle * COEFF : -angle * COEFF;
	col = ((int)(color(env->color, RED) * diffuse) << 16) +
	((int)(color(env->color, GREEN) * diffuse) << 8) +
	(int)(color(env->color, BLUE) * diffuse);
	return (col);
	// return ((col > 0) ? col : env->font_color);
}

void				reset_object(t_object *object)
{
	while (object)
	{
		object->set = false;
		object->norminter = 0;
		object->normlight = 0;
		object = object->next;
	}
}

void				trace(t_env *env)
{
	int		x;
	int		y;
	int		color;

	y = -1;
	x = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			reset_object(env->object);
			calc_ray(env, x, y);
			// if (y == HEIGHT/2 && x == WIDTH/2){
			if((env->nearest_object = calc_object(env->object, &env->ray)))
				{
					// printf("2\n\n\n\n\n");
					color = calc_light(env);
				}
			else
				color = BLACK;//env->font_color;
			*(env->img_addr + x + (y * env->size_line) / 4) = color;
			// }s
		}
	}
}

void			set_offset(t_object *object, t_ray *ray)
{
	t_sphere *o;

	o = object->ptr;
	object->offset = sub_tp3d(ray->pos, o->pos);
	set_tp3d(&object->rot, 0.0f, 1.0f, 0.0f);
}

int					main(int ac, char **av)
{
	t_env		*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		error(INIT, __LINE__ - 1, __FILE__, EXIT);
	if (ac == 2)
	{
		parse_file(av[1], env);
		set_ray(&env->ray, env);
		set_light(&env->light);
		trace(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		event(env);
		mlx_loop(env->mlx);
	}
	else
		error_arg(1, ac - 1, EXIT);
	return (0);
}
