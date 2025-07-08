#version 330 core

// "in" attributes
in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texture_coordinates;
in vec4 vertex_color;

// matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// object id
#define PLANE 0
#define BLOON 1
#define DART 2
#define MONKEY_LEVEL_1 3
#define MONKEY_LEVEL_2 4
#define WALL_FRONT 5
#define WALL_RIGHT 6
#define WALL_BACK 7
#define WALL_LEFT 8
uniform int object_id;

// shading model
#define PHONG 0
#define GOURAUD 1
uniform int shading_model;

// bloon level
uniform int bloon_level;

// AABB
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// texture
uniform sampler2D texture_image_0;
uniform sampler2D texture_image_1;
uniform sampler2D texture_image_2;
uniform sampler2D texture_image_3;
uniform sampler2D texture_image_4;
uniform sampler2D texture_image_5;
uniform sampler2D texture_image_6;
uniform sampler2D texture_image_7;
uniform sampler2D texture_image_8;
uniform sampler2D texture_image_9;

// color
out vec4 color;

// constants
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923


vec2 planar_projection(){
    float U = (position_model.x - bbox_min.x)/(bbox_max.x - bbox_min.x);
    float V = (position_model.y - bbox_min.y)/(bbox_max.y - bbox_min.y);

    return vec2(U, V);
}


vec2 spheric_projection(){
    vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
    vec4 p_point = bbox_center + (position_model - bbox_center)/(length(position_model - bbox_center));
    vec4 p_vector = p_point - bbox_center;

    float theta = atan(p_vector.x, p_vector.z);
    float phi = asin(p_vector.y);

    float U = (theta + M_PI)/(2*M_PI);
    float V = (phi + M_PI_2)/M_PI;

    return vec2(U, V);
}


void main(){
    if(shading_model == PHONG){
        vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
        vec4 camera_position = inverse(view) * origin;

        vec4 p = position_world;
        vec4 n = normalize(normal);
        vec4 l = normalize(vec4(-1.0,1.0,0.0,0.0));
        vec4 v = normalize(camera_position - p);
        vec4 h = normalize(v + l);

        float U = 0.0;
        float V = 0.0;

        vec3 Kd;
        vec3 Ks;
        vec3 Ka;
        float q;

        if(object_id == PLANE){
            U = texture_coordinates.x;
            V = texture_coordinates.y;

            Kd = texture(texture_image_0, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == BLOON){
            if(bloon_level == 1)
                Kd = texture(texture_image_1, planar_projection()).rgb;
            if(bloon_level == 2)
                Kd = texture(texture_image_2, planar_projection()).rgb;
            if(bloon_level == 3)
                Kd = texture(texture_image_3, planar_projection()).rgb;
            if(bloon_level == 4)
                Kd = texture(texture_image_4, planar_projection()).rgb;

            Ks = vec3(0.8,0.8,0.8);
            Ka = vec3(0.0,0.0,0.0);
            q = 50.0;
        }
        else if(object_id == DART){
            Kd = texture(texture_image_7, planar_projection()).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == MONKEY_LEVEL_1){
            Kd = texture(texture_image_5, planar_projection()).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == MONKEY_LEVEL_2){
            Kd = texture(texture_image_6, spheric_projection()).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == WALL_FRONT){
            U = texture_coordinates.x;
            V = texture_coordinates.y;

            Kd = texture(texture_image_8, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == WALL_RIGHT){
            U = texture_coordinates.y;
            V = texture_coordinates.x;

            Kd = texture(texture_image_9, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == WALL_BACK){
            U = texture_coordinates.x;
            V = texture_coordinates.y;

            Kd = texture(texture_image_8, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == WALL_LEFT){
            U = texture_coordinates.y;
            V = texture_coordinates.x;

            Kd = texture(texture_image_9, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }

        if(object_id >= PLANE && object_id <= MONKEY_LEVEL_2){
            vec3 I = vec3(1.0,1.0,1.0);
            vec3 Ia = vec3(0.2,0.2,0.2);

            vec3 lambert = Kd*I*max(0,dot(n,l));
            vec3 ambient = Ka*Ia;
            vec3 blinn_phong = Ks*I*pow(dot(n,h),q);

            color.rgb = lambert + ambient + blinn_phong;
            color.a = 1;
        }
        else{
            color.rgb = Kd;
            color.a = 1;
        }
    }
    else if(shading_model == GOURAUD){
        color = vertex_color;
    }

    color.rgb = pow(color.rgb, vec3(1.0/2.2));
}
