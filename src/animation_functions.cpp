#include "animation_functions.hpp"

glm::vec4 bezier_spline(std::vector<glm::vec4> &points, float delta_time){

    int seg;
    glm:: vec4 p1, p2, p3;
    float t;

    seg = static_cast<int>(floor(delta_time / 4.0f));

    p1 = points[seg*2]; 
    p2 = points[seg*2+1];
    p3 = points[seg*2+2];

    t = (delta_time - seg * 4.0f) / 4.0f;

    float b1 = pow(1 - t, 2);
    float b2 = 2 * t * (1 - t);
    float b3 = pow(t, 2);

    return b1 * p1 + b2 *p2 + b3 * p3; 
}
