#pragma once

// C/C++ headers
#include <cmath>
#include <vector>

// GLM headers
#include <glm/vec4.hpp>

// Local headers
#include "matrices.h"

glm::vec4 bezier_spline(std::vector<glm::vec4> &points, float time);