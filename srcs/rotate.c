/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:15:16 by lgatibel          #+#    #+#             */
/*   Updated: 2017/04/13 17:16:11 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_p3d			rotate_tp3d(t_p3d *ray, t_p3d *rot)
{
	t_p3d	matx;
	t_p3d	maty;
	t_p3d	matz;
	t_p3d	res;

	set_tp3d(&matx, cos(rot->y) * cos(rot->z),
	cos(rot->y) * (-sin(rot->z)),
	sin(rot->y));
	set_tp3d(&maty, (-sin(rot->x)) * (-sin(rot->y)) * cos(rot->z) +
	cos(rot->x) * sin(rot->z), (-sin(rot->x)) * (-sin(rot->y)) *
	(-sin(rot->z)) + cos(rot->x) * cos(rot->z), (-sin(rot->x)) * cos(rot->y));
	set_tp3d(&matz, cos(rot->x) * (-sin(rot->y)) * cos(rot->z) + sin(rot->x) *
	sin(rot->z), cos(rot->x) * (-sin(rot->y)) * (-sin(rot->z)) + sin(rot->x) *
	cos(rot->z), cos(rot->x) * cos(rot->y));
	res.x = dot_product_tp3d(matx, *ray);
	res.y = dot_product_tp3d(maty, *ray);
	res.z = dot_product_tp3d(matz, *ray);
	return (res);
}
