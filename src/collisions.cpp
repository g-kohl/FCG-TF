#include "collisions.hpp"

// Function that checks the collision of a point with a sphere
// Used to check if a dart is in the range of a monkey
bool is_point_in_range(glm::vec4 point_p, glm::vec4 point_c, float range){

    glm::vec4 d_vector = point_p - point_c;
    float d_mag = norm(d_vector);

    return d_mag <= range;
}

// Function that checks the intersection of a vector with a bounding box, using the slab method
// We just need to check the collision only in 2 dimensions (x and z)
// Used to check dart collision
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

// Function that checks the collision of a sphere with a bounding box. Used to check camera collision
bool is_sphere_hit_bbox(glm::vec4 min_bbox, glm::vec4 max_bbox, glm::vec4 point_c, float sphere_r){

    glm::vec4 p_close = glm::vec4(point_c.x, point_c.y, point_c.z, 1.0f);

    for(int i = 0; i < 3; i++){

        if(point_c[i] < min_bbox[i]){
            p_close[i] = min_bbox[i];            

        }else if(point_c[i] > max_bbox[i]) 
            p_close[i] = max_bbox[i];
    }

    return is_point_in_range(p_close, point_c, sphere_r);
}

// Function that checks the intersection of two bounding boxes. 
// Used to prevent one monkey from overlapping another
bool is_bbox_hit_bbox(glm::vec4 min_bbox_fir, glm::vec4 max_bbox_fir, glm::vec4 min_bbox_sec, glm::vec4 max_bbox_sec){

    if(min_bbox_sec.x <= max_bbox_fir.x && max_bbox_sec.x >= min_bbox_fir.x){
        if(min_bbox_sec.z <= max_bbox_fir.z && max_bbox_sec.z >= min_bbox_fir.z)
            return true;
    }

    return false;
}