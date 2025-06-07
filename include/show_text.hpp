#pragma once

// C++ headers
#include <string>

// Local headers
#include "matrices.h"
#include "globals.hpp"
#include "textrendering.hpp"

void TextRendering_ShowModelViewProjection(GLFWwindow* window, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec4 p_model);
void TextRendering_ShowProjection(GLFWwindow* window);
void TextRendering_ShowFramesPerSecond(GLFWwindow* window);
