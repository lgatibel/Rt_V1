/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 10:40:46 by lgatibel          #+#    #+#             */
/*   Updated: 2017/01/23 14:29:32 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void			set_plane(t_env *env, int fd, t_object **obj)
{
	int			i;
	char		**tab;
	char		ok[4];
	t_plane		*plane;

	i = -1;
	plane = (t_plane *)malloc(sizeof(t_plane));
	(*obj)->ptr = plane;
	(*obj)->type = PLANE;
	ft_bzero(&ok, 4);
	while (++i < 3 && (get_next_line(fd, &env->line)) > 0 &&
			(tab = ft_strsplit(env->line, ' ')))
	{
		print_line(&env->line);
		if (!ft_strcmp(ft_strtrim(tab[0]), "origin"))
			ok[0] = set_vecteur(&tab[1], &plane->pos);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "norm"))
			ok[1] = set_rotation_vecteur(&tab[1], &plane->normal);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "color"))
			ok[2] = set_color(&tab[1], &(*obj)->color);
	}
	if (!args_required(ok, 3))
		err(__FILE__, __LINE__, "bad parameter", EXIT);
}

static void			set_cylinder(t_env *env, int fd, t_object **obj)
{
	int			i;
	char		**tab;
	char		ok[5];
	t_cylinder	*cylinder;

	i = -1;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	(*obj)->ptr = cylinder;
	(*obj)->type = CYLINDER;
	ft_bzero(&ok, 5);
	while (++i < 4 && (get_next_line(fd, &env->line)) > 0 &&
			(tab = ft_strsplit(env->line, ' ')))
	{
		print_line(&env->line);
		if (!ft_strcmp(ft_strtrim(tab[0]), "origin"))
			ok[0] = set_vecteur(&tab[1], &cylinder->pos);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "rot"))
			ok[1] = set_rotation_vecteur(&tab[1], &cylinder->rot);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "radius"))
			ok[2] = set_radius(&tab[1], &cylinder->radius);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "color"))
			ok[3] = set_color(&tab[1], &(*obj)->color);
	}
	if (!args_required(ok, 4))
		err(__FILE__, __LINE__, "bad parameter", EXIT);
}

static void			set_sphere(t_env *env, int fd, t_object **obj)
{
	int			i;
	char		**tab;
	char		ok[5];
	t_sphere	*sphere;

	i = -1;
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	(*obj)->ptr = sphere;
	(*obj)->type = SPHERE;
	ft_bzero(&ok, 5);
	while (++i < 4 && (get_next_line(fd, &env->line)) > 0 &&
			(tab = ft_strsplit(env->line, ' ')))
	{
		print_line(&env->line);
		if (!ft_strcmp(ft_strtrim(tab[0]), "origin"))
			ok[0] = set_vecteur(&tab[1], &sphere->pos);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "rot"))
			ok[1] = set_rotation_vecteur(&tab[1], &sphere->rot);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "radius"))
			ok[2] = set_radius(&tab[1], &sphere->radius);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "color"))
			ok[3] = set_color(&tab[1], &(*obj)->color);
	}
	if (!args_required(ok, 4))
		err(__FILE__, __LINE__, "bad parameter", EXIT);
}

static void			set_cone(t_env *env, int fd, t_object **obj)
{
	int		i;
	char	**tab;
	char	ok[5];
	t_cone	*cone;

	i = -1;
	cone = (t_cone *)malloc(sizeof(t_cone));
	(*obj)->ptr = cone;
	(*obj)->type = CONE;
	ft_bzero(&ok, 5);
	while (++i < 4 && (get_next_line(fd, &env->line)) > 0 &&
			(tab = ft_strsplit(env->line, ' ')))
	{
		print_line(&env->line);
		if (!ft_strcmp(ft_strtrim(tab[0]), "origin"))
			ok[0] = set_vecteur(&tab[1], &cone->pos);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "rot"))
			ok[1] = set_rotation_vecteur(&tab[1], &cone->rot);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "radius"))
			ok[2] = set_radius(&tab[1], &cone->radius);
		else if (!ft_strcmp(ft_strtrim(tab[0]), "color"))
			ok[3] = set_color(&tab[1], &(*obj)->color);
	}
	if (!args_required(ok, 4))
		err(__FILE__, __LINE__, "bad parameter", EXIT);
}

void				set_object(t_env *env, int fd, t_object **object)
{
	int			i;
	char		**tab;
	t_object	*obj;

	i = -1;
	while (get_next_line(fd, &env->line) > 0 && ft_strcmp(ft_strtrim(env->line),
				"###END"))
	{
		ft_putendl(env->line);
		malloc_object(&obj, object, ++i);
		tab = ft_strsplit(env->line, ' ');
		if (tab && !ft_strcmp(ft_strtrim(tab[0]), "#CONE"))
			set_cone(env, fd, &obj);
		else if (tab && !ft_strcmp(ft_strtrim(tab[0]), "#CYLINDER"))
			set_cylinder(env, fd, &obj);
		else if (tab && !ft_strcmp(ft_strtrim(tab[0]), "#PLANE"))
			set_plane(env, fd, &obj);
		else if (tab && !ft_strcmp(ft_strtrim(tab[0]), "#SPHERE"))
			set_sphere(env, fd, &obj);
		else
			err(__FILE__, __LINE__, "bad object defined", EXIT);
	}
}
