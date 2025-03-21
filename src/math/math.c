#include "minirt.h"

int imin(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int imax(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

// float fmin(float a, float b)
// {
// 	if (a < b)
// 		return (a);
// 	else
// 		return (b);
// }

// float fmax(float a, float b)
// {
// 	if (a > b)
// 		return (a);
// 	else
// 		return (b);
// }

void normalize(float vector[3])
{
	float temp;
	float magnitude;

	magnitude = sqrtf(vector[0] * vector[0]
				+ vector[1] * vector[1]
				+ vector[2] * vector[2]);
	temp = 1 / magnitude;
	vector[0] *= temp;
	vector[1] *= temp;
	vector[2] *= temp;
}

void normalize2(float vector[3], float *magnitude)
{
	float temp;

	*magnitude = sqrtf(vector[0] * vector[0]
				+ vector[1] * vector[1]
				+ vector[2] * vector[2]);
	temp = 1 / *magnitude;
	vector[0] *= temp;
	vector[1] *= temp;
	vector[2] *= temp;
}

float	dot_13_13(float a[3], float b[3])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void	vec_substr(float p2[3], float p1[3], float result[3])
{
	int i;

	i = -1;
	while (++i < 3)
		result[i] = p2[i] - p1[i]; 
}

void	vec_add_inplace(float p1[3], float p2[3])
{
	int i;

	i = -1;
	while (++i < 3)
		p1[i] += p2[i]; 
}
void	cpy_vec(float v1[3], float v2[3])
{
	v2[0] = v1[0];
	v2[1] = v1[1];
	v2[2] = v1[2];
}

void	scale_vec(float v[3], float amp)
{
	v[0] *= amp;
	v[1] *= amp;
	v[2] *= amp;
}

void	ft_swap(float *t1, float *t2)
{
	float tmp;

	tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}


int	abs_int(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
void	cprod_13_13(float a[3], float b[3], float res[3])
{
	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

float triple_scalar(float a[3], float b[3], float c[3]) 
{
    return a[0] * (b[1] * c[2] - b[2] * c[1]) +
           a[1] * (b[2] * c[0] - b[0] * c[2]) +
           a[2] * (b[0] * c[1] - b[1] * c[0]);
}