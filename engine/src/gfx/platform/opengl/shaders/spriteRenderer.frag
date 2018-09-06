layout(location = 0) out vec4 color;

in DATA {
  vec4 position;
  vec2 uv;
  float tid;
  vec4 color;
} fs_in;

uniform sampler2D textures[32];

uniform vec2 cursor;

void main() {
  vec4 final = fs_in.color;

  if (fs_in.tid > 0.0) {
    int tid = int(fs_in.tid - 0.5);
    final = fs_in.color * texture(textures[tid], fs_in.uv);
  }

  float intensity = 1.0 / length(fs_in.position.xy - cursor) * 10.0;

  // color = final;
  color = final * intensity;
}
