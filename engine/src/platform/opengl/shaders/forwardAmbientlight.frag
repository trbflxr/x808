R"(
in vec2 uv0;
in mat3 tbnMat0;
in vec3 worldPos0;

out vec4 out_Color;

uniform vec4 color;
uniform float intensity;
uniform vec3 eyePos;

uniform sampler2D diffuse;
uniform sampler2D dispMap;

uniform float dispMapScale;
uniform float dispMapBias;

void main() {
  vec3 directionToEye = normalize(eyePos - worldPos0);
  vec2 uv = CalcParallaxUV(dispMap, tbnMat0, directionToEye, uv0, dispMapScale, dispMapBias);

  out_Color = texture(diffuse, uv) * intensity * color;
}
)"
