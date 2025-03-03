#include "minirt.h"

// static t_intersect_result	intersection_test_aabb(t_aabb *aabb, float dir[3], float src[3]);

float	intersection_test_bvh_root(t_aabb *node, t_shoot *shoot)
{
	t_intersect_result	t;

	t = intersection_test_aabb(node, shoot->dir, shoot->src);
	if (t.min == -1)
		return (0);
	return (intersection_test_bvh(node, shoot));
}

float	intersection_test_bvh(t_aabb *node, t_shoot *shoot)
{
	float				t;
	t_intersect_result	t_left;
	t_intersect_result	t_right;

	if (!node->childs)
		return (visibility_intersection_tests_leafs(node->group, shoot, node->group_size));
	t_left 	= intersection_test_aabb(&node->childs[0], shoot->dir, shoot->src);
	t_right = intersection_test_aabb(&node->childs[1], shoot->dir, shoot->src);
	if (t_left.min == -1 && t_right.min == -1)
		return (0);
	else if (t_right.min == -1)
		return (intersection_test_bvh(&node->childs[0], shoot));
	else if (t_left.min == -1)
		return (intersection_test_bvh(&node->childs[1], shoot));
	else if (t_left.min < t_right.min)
	{
		t = intersection_test_bvh(&node->childs[0], shoot);
		if (t > 0)
			return (t);
		return (intersection_test_bvh(&node->childs[1], shoot));
	}
	//else if (t_left.min != -1 && t_right.min != -1 && t_left.min >= t_right.min)
	t = intersection_test_bvh(&node->childs[1], shoot);
	if (t > 0)
		return (t);
	return (intersection_test_bvh(&node->childs[0], shoot));
}




/// SHADOW AABB ////

float	shadow_test_bvh_root(t_shoot *shoot, t_aabb *node, float shadow_ray[3], float dist_light)
{
	t_intersect_result	t;

	t = intersection_test_aabb(node, shadow_ray, shoot->hit_pt);
	if (t.min == -1)
		return (0);
	return (shadow_test_bvh(shoot, node, shadow_ray, dist_light));
}


float	shadow_test_bvh(t_shoot *shoot, t_aabb *node, float shadow_ray[3], float dist_light)
{
	float				t;
	t_intersect_result	t_left;
	t_intersect_result	t_right;

	if (!node->childs)
		return (shadow_intersection_tests_leaf(shoot, node->group, shadow_ray, dist_light, node->group_size));
	t_left 	= intersection_test_aabb(&node->childs[0], shadow_ray, shoot->hit_pt);
	t_right = intersection_test_aabb(&node->childs[1], shadow_ray, shoot->hit_pt);
	if (t_right.min == -1 && t_left.min == -1)
		return (0);
	if (t_right.min == -1)
		return (shadow_test_bvh(shoot, &node->childs[0], shadow_ray, dist_light));
	if (t_left.min == -1)
		return (shadow_test_bvh(shoot, &node->childs[1], shadow_ray, dist_light));
	if (t_left.max - t_left.min > t_right.max - t_right.min)
	// if (t_left.min > t_right.min) // changer cette logique pour "box ou le ray parcouru est le plus long!..."
	{
		t = shadow_test_bvh(shoot, &node->childs[0], shadow_ray, dist_light);
		if (t != 0)
			return (t);
		return (shadow_test_bvh(shoot, &node->childs[1], shadow_ray, dist_light));
	}
	t = shadow_test_bvh(shoot, &node->childs[1], shadow_ray, dist_light);
	if (t != 0)
		return (t);
	return (shadow_test_bvh(shoot, &node->childs[0], shadow_ray, dist_light));
}




/*
static t_intersect_result	intersection_test_aabb(t_aabb *aabb, float dir[3], float src[3])
{
    t_intersect_result t = { 0.0f, FLT_MAX };

    // Load dir, src, pt_min, and pt_max into AVX registers
    // __m128 v_dir = _mm_loadu_ps(dir);      // dir[x], dir[y], dir[z], garbage
    // __m128 v_src = _mm_loadu_ps(src);      // src[x], src[y], src[z], garbage
    // __m128 v_min = _mm_loadu_ps(aabb->pt_min); // pt_min[x], pt_min[y], pt_min[z], garbage
    // __m128 v_max = _mm_loadu_ps(aabb->pt_max); // pt_max[x], pt_max[y], pt_max[z], garbage
	__m128 v_dir = _mm_setr_ps(dir[0], dir[1], dir[2], 0.0f);
	__m128 v_src = _mm_setr_ps(src[0], src[1], src[2], 0.0f);
	__m128 v_min = _mm_setr_ps(aabb->pt_min[0], aabb->pt_min[1], aabb->pt_min[2], 0.0f);
	__m128 v_max = _mm_setr_ps(aabb->pt_max[0], aabb->pt_max[1], aabb->pt_max[2], 0.0f);


    // Compute absolute dir and check for near-zero values (parallel check)
    __m128 v_abs_dir = _mm_andnot_ps(_mm_set1_ps(-0.0f), v_dir); // fabs(dir)
    __m128 v_near_zero = _mm_cmplt_ps(v_abs_dir, _mm_set1_ps(1e-8f)); // Check if dir[i] < EPSILON

    // Check if src is outside AABB for parallel rays
    __m128 v_outside_min = _mm_cmplt_ps(v_src, v_min);
    __m128 v_outside_max = _mm_cmpgt_ps(v_src, v_max);
    __m128 v_fail = _mm_and_ps(_mm_or_ps(v_outside_min, v_outside_max), v_near_zero); // Fail if parallel and outside

    // If any component fails, return immediately
    if (_mm_movemask_ps(v_fail)) {
        t.min = -1.0f;
        return t;
    }

    // Compute reciprocal (1.0 / dir) where dir is not zero
    __m128 v_ood = _mm_blendv_ps(_mm_rcp_ps(v_dir), _mm_setzero_ps(), v_near_zero);

    // Compute intersection distances
    __m128 v_t1 = _mm_mul_ps(_mm_sub_ps(v_min, v_src), v_ood);
    __m128 v_t2 = _mm_mul_ps(_mm_sub_ps(v_max, v_src), v_ood);

    // Ensure t1 <= t2 (swap where necessary)
    __m128 v_tmin = _mm_min_ps(v_t1, v_t2);
    __m128 v_tmax = _mm_max_ps(v_t1, v_t2);

    // Compute final min/max values
    t.min = fmaxf(fmaxf(t.min, _mm_cvtss_f32(v_tmin)), fmaxf(_mm_cvtss_f32(_mm_shuffle_ps(v_tmin, v_tmin, _MM_SHUFFLE(1, 1, 1, 1))),
                                                               _mm_cvtss_f32(_mm_shuffle_ps(v_tmin, v_tmin, _MM_SHUFFLE(2, 2, 2, 2)))));

    t.max = fminf(fminf(t.max, _mm_cvtss_f32(v_tmax)), fminf(_mm_cvtss_f32(_mm_shuffle_ps(v_tmax, v_tmax, _MM_SHUFFLE(1, 1, 1, 1))),
                                                               _mm_cvtss_f32(_mm_shuffle_ps(v_tmax, v_tmax, _MM_SHUFFLE(2, 2, 2, 2)))));

    // If t.min > t.max, return failure
    if (t.min > t.max)
        t.min = -1.0f;

    return t;
}
*/