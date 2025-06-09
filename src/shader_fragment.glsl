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

    float U = 0.0;
    float V = 0.0;

    if(object_id == PLANE){
        U = texcoords.x;
        V = texcoords.y;
    }

    vec3 Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
    float lambert = max(0,dot(n,l));

    color.rgb = Kd0 * (lambert + 0.01);
    color.a = 1;
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}