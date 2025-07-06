#pragma once

// C/C++ headers
#include <algorithm>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"

bool is_point_in_range(glm::vec4 point_p, glm::vec4 point_c, float range);
bool is_ray_hit_bbox(glm::vec4 b_min, glm::vec4 b_max, glm::vec4 point_c, glm::vec4 ray);
bool is_sphere_hit_bbox(glm::vec4 min_bbox, glm::vec4 max_bbox, glm::vec4 point_c, float sphere_r);
bool is_bbox_hit_bbox(glm::vec4 min_bbox_fir, glm::vec4 max_bbox_fir, glm::vec4 min_bbox_sec, glm::vec4 max_bbox_sec);