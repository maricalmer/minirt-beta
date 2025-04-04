/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlemaire <dlemaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:32:55 by dlemaire          #+#    #+#             */
/*   Updated: 2025/03/29 16:13:43 by dlemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	print_error_2(int errnum);

void	print_error(int errnum)
{
	if (errnum == 1)
		printf("\n%sError%s%sWrong args%s\n", RED_BG_START, COLOR_END,
			RED_TXT_START, COLOR_END);
	else if (errnum == 2)
		printf("\n%sError%s%sWrong input file%s\n", RED_BG_START, COLOR_END,
			RED_TXT_START, COLOR_END);
	else if (errnum == 3)
		printf("\n%sError%s%s%s%s\n", RED_BG_START, COLOR_END, RED_TXT_START,
			strerror(errno), COLOR_END);
	else if (errnum == 4)
		printf("\n%sError%s%sWrong set of light, cam or ambient%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 5)
		printf("\n%sError%s%sWrong set of element types%s\n", RED_BG_START,
			COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 6)
		printf("\n%sError%s%sWrong settings for ambient lighting element%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 7)
		printf("\n%sError%s%sWrong settings for camera element%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else
		print_error_2(errnum);
}

static void	print_error_2(int errnum)
{
	if (errnum == 8)
		printf("\n%sError%s%sWrong settings for light element%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 9)
		printf("\n%sError%s%sWrong settings for sphere element%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 10)
		printf("\n%sError%s%sWrong settings for plane element%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 11)
		printf("\n%sError%s%sWrong settings for cylinder element%s\n",
			RED_BG_START, COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 12)
		printf("\n%sError%s%sWrong settings for tri element%s\n", RED_BG_START,
			COLOR_END, RED_TXT_START, COLOR_END);
	else if (errnum == 13)
		printf("\n%sError%s%sWrong settings for obj element%s\n", RED_BG_START,
			COLOR_END, RED_TXT_START, COLOR_END);
}
