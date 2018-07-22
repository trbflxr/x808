R"(
#shader fragment
#version 330

in vec2 uv0;
in mat3 tbnMat0;
in vec3 worldPos0;

out vec4 out_Color;

uniform sampler2D diffuse;
uniform sampler2D normalMap;
)"
