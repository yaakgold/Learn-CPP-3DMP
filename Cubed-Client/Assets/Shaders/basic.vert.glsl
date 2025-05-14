#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

layout(location = 0) out vec3 out_color;
layout(location = 1) out vec3 out_normal;

vec3 triangle_colors[4] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 0.0, 1.0)
);

layout(push_constant) uniform PushConstants
{
	mat4 ViewProjection;
    mat4 Transform;
} u_PushConstants;

void main()
{
    gl_Position = u_PushConstants.ViewProjection 
                    * u_PushConstants.Transform 
                    * vec4(a_Position, 1.0);

    out_normal = normalize(transpose(inverse(mat3(u_PushConstants.Transform))) * a_Normal);
    out_color = a_Normal * 0.5 + 0.5;
}
