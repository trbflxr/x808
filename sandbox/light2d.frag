layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
in float tid0;

in vec4 position0;

uniform sampler2D textures[@MAX_TEXTURES];

uniform vec4 lightColor;
uniform vec2 lightPosition;

void main() {
  vec4 final = color0;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);
    final = color0 * texture(textures[tid], uv0);
  }

  float intensity = 1.0 / length(position0.xy - lightPosition);

  color = final * (lightColor * intensity * 20);
//  color = final * intensity;
//  color = final;
}
