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
            U = texture_coordinates.x;
            V = texture_coordinates.y;

            if(bloon_level == 1)
                Kd = texture(texture_image_1, vec2(U,V)).rgb;
            if(bloon_level == 2)
                Kd = texture(texture_image_2, vec2(U,V)).rgb;
            if(bloon_level == 3)
                Kd = texture(texture_image_3, vec2(U,V)).rgb;
            if(bloon_level == 4)
                Kd = texture(texture_image_4, vec2(U,V)).rgb;

            Ks = vec3(0.8,0.8,0.8);
            Ka = vec3(0.0,0.0,0.0);
            q = 50.0;
        }
        else if(object_id == DART){
            float minx = bbox_min.x;
            float maxx = bbox_max.x;

            float miny = bbox_min.y;
            float maxy = bbox_max.y;

            float minz = bbox_min.z;
            float maxz = bbox_max.z;

            U = (position_model.x - minx)/(maxx - minx);
            V = (position_model.y - miny)/(maxy - miny);

            Kd = texture(texture_image_7, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == MONKEY_LEVEL_1){
            float minx = bbox_min.x;
            float maxx = bbox_max.x;

            float miny = bbox_min.y;
            float maxy = bbox_max.y;

            float minz = bbox_min.z;
            float maxz = bbox_max.z;

            U = (position_model.x - minx)/(maxx - minx);
            V = (position_model.y - miny)/(maxy - miny);

            Kd = texture(texture_image_5, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == MONKEY_LEVEL_2){
            float minx = bbox_min.x;
            float maxx = bbox_max.x;

            float miny = bbox_min.y;
            float maxy = bbox_max.y;

            float minz = bbox_min.z;
            float maxz = bbox_max.z;

            U = (position_model.x - minx)/(maxx - minx);
            V = (position_model.y - miny)/(maxy - miny);

            Kd = texture(texture_image_6, vec2(U,V)).rgb;
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