#version 330 core

// "in" attributes
in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texcoords;

// matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// object id
#define BALLOON 0
#define PLANE  1
#define MONKEY 2
#define BIGMONKEY 3
uniform int object_id;

// AABB
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// texture
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;

// color
out vec4 color;

// constants
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main(){
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));
    vec4 v = normalize(camera_position - p);
    vec4 h = normalize(v + l);

    float U = 0.0;
    float V = 0.0;

    vec3 Kd;
    vec3 Ks;
    vec3 Ka;
    float q;

    if(object_id == BALLOON){
        U = texcoords.x;
        V = texcoords.y;

        Kd = texture(TextureImage1, vec2(U,V)).rgb;
        Ks = vec3(0.8,0.8,0.8);
        Ka = vec3(0.0,0.0,0.0);
        q = 50.0;
    }
    else if(object_id == PLANE){
        U = texcoords.x;
        V = texcoords.y;

        Kd = texture(TextureImage0, vec2(U,V)).rgb;
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }
    else if(object_id == MONKEY){
        U = texcoords.x;
        V = texcoords.y;

        Kd = texture(TextureImage2, vec2(U,V)).rgb;
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }
    else if(object_id == BIGMONKEY){
        U = texcoords.x;
        V = texcoords.y;

        Kd = texture(TextureImage2, vec2(U,V)).rgb;
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
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}