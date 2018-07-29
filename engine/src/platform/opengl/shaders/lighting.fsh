R"(
#shader fragment
#version 330

in vec2 uv0;
in mat3 tbnMat0;
in vec3 worldPos0;
in vec4 shadowMapUV0;

out vec4 out_Color;

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform float sys_DispMapScale;
uniform float sys_DispMapBias;

uniform sampler2D shadowMap;
uniform float sys_ShadowBias;
uniform vec2 sys_ShadowTexelSize;
)"
