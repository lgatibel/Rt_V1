/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:19:35 by lgatibel          #+#    #+#             */
/*   Updated: 2016/11/02 14:54:18 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Rtv1.h>

int					main(void)
{
	void		*mlx;

	mlx = mlx_init();
	mlx_new_window(mlx, 1000, 1000, "hello");
	return (0);
}
