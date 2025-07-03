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
#define MONKEY_LEVEL_1 2
#define MONKEY_LEVEL_2 3
uniform int object_id;

// shading model
#define PHONG 0
#define GOURAUD 1
uniform int shading_model;

// AABB
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// texture
uniform sampler2D texture_image_0;
uniform sampler2D texture_image_1;
uniform sampler2D texture_image_2;

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

            Kd = texture(texture_image_1, vec2(U,V)).rgb;
            Ks = vec3(0.8,0.8,0.8);
            Ka = vec3(0.0,0.0,0.0);
            q = 50.0;
        }
        else if(object_id == MONKEY_LEVEL_1){
            U = texture_coordinates.x;
            V = texture_coordinates.y;

            Kd = texture(texture_image_2, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == MONKEY_LEVEL_2){
            U = texture_coordinates.x;
            V = texture_coordinates.y;

            Kd = texture(texture_image_2, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }

        vec3 I = vec3(1.0,1.0,1.0);
        vec3 Ia = vec3(0.2,0.2,0.2);

        vec3 lambert = Kd*I*max(0,dot(n,l));
        vec3 ambient = Ka*Ia;
        vec3 blinn_phong = Ks*I*pow(dot(n,h),q);

        color.rgb = lambert + ambient + blinn_phong;
        color.a = 1;
    }
    else if(shading_model == GOURAUD){
        color = vertex_color;
    }

    color.rgb = pow(color.rgb, vec3(1.0/2.2));
}