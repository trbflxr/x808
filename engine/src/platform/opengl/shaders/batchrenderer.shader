R"(
#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
uniform vec2 u_LightPos;
//uniform mat4 sys_ModelMatrix;

out DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
	vec2 light_pos;
} vs_out;

void main()
{
	gl_Position = (sys_ProjectionMatrix * sys_ViewMatrix) * position;

	vs_out.position = position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
	vs_out.light_pos = u_LightPos;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
	vec2 light_pos;
} fs_in;

uniform sampler2D textures[32];

void main()
{
    float intensity = 7.0 / length(fs_in.position.xy - fs_in.light_pos);
	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.uv);
	}
	color = texColor * intensity;
	//color = texColor;
}
)"