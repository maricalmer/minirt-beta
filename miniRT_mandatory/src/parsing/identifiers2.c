/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 10:59:22 by dlemaire          #+#    #+#             */
/*   Updated: 2025/03/26 11:33:10 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_sphere(char *specs)
{
	return (specs[0] == 's' && specs[1] == 'p' && specs[2] == ' ');
}

int	is_cylinder(char *specs)
{
	return (specs[0] == 'c' && specs[1] == 'y' && specs[2] == ' ');
}
