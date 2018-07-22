R"(
#shader fragment
#version 330

in vec2 uv0;
in mat3 tbnMat0;
in vec3 worldPos0;

out vec4 out_Color;

uniform vec4 sys_Color;
uniform float sys_Intensity;
uniform vec3 sys_EyePos;

uniform sampler2D sampler;
uniform sampler2D dispMap;

uniform float sys_DispMapScale;
uniform float sys_DispMapBias;
)"
