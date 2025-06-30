#version 330 core

// "in" attributes
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;

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

// texture
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;

// vertex attributes
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec4 vertex_color;

void main()
{
    // vertex position in NDC
    gl_Position = projection * view * model * model_coefficients;

    // vertex position in world coordinates
    position_world = model * model_coefficients;

    // vertex position in local coordinates
    position_model = model_coefficients;

    // vertex normal
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    // texture coordinates
    texcoords = texture_coefficients;

    if(shading_model == PHONG){
        vertex_color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else if(shading_model == GOURAUD){
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

        if(object_id == BLOON){
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
        else if(object_id == MONKEY_LEVEL_1){
            U = texcoords.x;
            V = texcoords.y;

            Kd = texture(TextureImage2, vec2(U,V)).rgb;
            Ks = vec3(0.0,0.0,0.0);
            Ka = vec3(0.0,0.0,0.0);
            q = 1.0;
        }
        else if(object_id == MONKEY_LEVEL_2){
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

        vertex_color.rgb = lambert + ambient + blinn_phong;
        vertex_color.a = 1;
    }
}

