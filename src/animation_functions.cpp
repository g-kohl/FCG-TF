#include "animation_functions.hpp"

// Function that calculates the next point given the control points of a cubic bezier curve
// Used for the movement of bloons
glm::vec4 bezierSpline(std::vector<glm::vec4> &points, float delta_time){
    int seg;
    glm:: vec4 p1, p2, p3, p4;
    float t;

    // Check which curve the balloon is on according to the time
    seg = static_cast<int>(floor(delta_time / 2.0f));

    p1 = points[seg*3]; 
    p2 = points[seg*3+1];
    p3 = points[seg*3+2];
    p4 = points[seg*3+3];

    t = (delta_time - seg * 2.0f) / 2.0f;

    float b1 = pow(1 - t, 3);
    float b2 = 3 * t * pow(1 - t, 2);
    float b3 = 3 * pow(t, 2) * (1 - t);
    float b4 = pow(t, 3);

    return b1 * p1 + b2 * p2 + b3 * p3 + b4 * p4; 
}
