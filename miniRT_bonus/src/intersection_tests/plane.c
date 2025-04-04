/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlemaire <dlemaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:55:06 by hruiz-fr          #+#    #+#             */
/*   Updated: 2025/03/19 18:55:34 by dlemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	test_plane(t_object *obj, float ray[3], float origin[3])
{
	float	pts_d[3];
	float	a;
	float	b;

	a = dot_13_13(obj->geo.pl.normal, ray);
	if (a < EPSILON && a > -EPSILON)
		return (0);
	vec_substr (obj->geo.pl.point, origin, pts_d);
	b = dot_13_13(obj->geo.pl.normal, pts_d);
	if ((a < 0 && b > 0) || (a > 0 && b < 0))
		return (0);
	return (b / a);
}
