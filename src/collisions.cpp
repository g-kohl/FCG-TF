#include "collisions.hpp"

bool point_in_range(glm::vec4 point_p, glm::vec4 point_c, float range){

    glm::vec4 d_vector = point_p - point_c;
    float d_mag = norm(d_vector);

    return d_mag <= range;
}

bool is_ray_hit_bbox(glm::vec4 b_min, glm::vec4 b_max, glm::vec4 point_c, glm::vec4 ray){

    float ray_mag = norm(ray); 
    glm::vec4 d_vector = ray / ray_mag;

    float t_close = 0.0f;
    float t_far = ray_mag;

    float x_min, x_max, y_min, y_max;

    if(d_vector.x != 0.0f){

        x_min = (b_min.x - point_c.x) / ray.x;
        x_max = (b_max.x - point_c.x) / ray.x;

        t_close = std::max(t_close, std::min(x_min, x_max));
        t_far = std::min(t_far, std::max(x_min, x_max));
    }

    if(d_vector.z != 0.0f){

        y_min = (b_min.z - point_c.z) / ray.z;
        y_max = (b_max.z - point_c.z) / ray.z;

        t_close = std::max(t_close, std::min(y_min, y_max));
        t_far = std::min(t_far, std::max(y_min, y_max));
    }

    if(t_close > t_far){
        return false;

    }else return t_close <= ray_mag;
}