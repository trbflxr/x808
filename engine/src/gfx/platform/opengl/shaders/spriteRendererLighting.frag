#define MAX_LIGHTS 64

struct Light {
  vec2 position;
  vec2 OFFSET01;
  vec4 colorIntencity;
};

layout(location = 0) out vec4 color;

in vec4 position0;
in vec2 uv0;
in float tid0;
in vec4 color0;

uniform sampler2D textures[32];

uniform int lightCount;

layout(std140) uniform LightBlock { Light lights[MAX_LIGHTS]; };

void main() {
  vec4 final = color;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);
    final = color0 * texture(textures[tid], uv0);
  }

  //todo: improve
  vec4 lightColor;
  for (int i = 0; i < lightCount; i++) {
    float intensity = 1.0 / length(position0.xy - lights[i].position) * lights[i].colorIntencity.w;
    lightColor += vec4(lights[i].colorIntencity.xyz, 1.0) * intensity;
  }

  color = final * lightColor;
}
