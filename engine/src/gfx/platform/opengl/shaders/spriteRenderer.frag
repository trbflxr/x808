layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
in float tid0;

uniform sampler2D textures[32];

void main() {
  vec4 final = color0;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);
    final = color0 * texture(textures[tid], uv0);
  }

  color = final;
}
