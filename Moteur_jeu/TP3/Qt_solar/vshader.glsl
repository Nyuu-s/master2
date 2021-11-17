#version 150

uniform mat4 mvp_matrix;
uniform mat4 transform;

in vec4 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;



uniform sampler2D heightmap;
uniform sampler2D texture;
uniform sampler2D snow;
uniform sampler2D rock;



//! [0]
void main()
{
   // float height = texture2D(heightmap, a_texcoord).p;

    // Calculate vertex position in screen space

    gl_Position = mvp_matrix * transform * vec4(a_position.x, a_position.y, a_position.z , 1.0f);

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
//! [0]
