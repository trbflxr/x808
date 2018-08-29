layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in float tid;
layout(location = 3) in vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out DATA {
  vec4 position;
  vec2 uv;
  float tid;
  vec4 color;
} vs_out;

void main() {
  gl_Position = (projectionMatrix * viewMatrix) * position;

  vs_out.position = position;
  vs_out.uv = uv;
  vs_out.tid = tid;
  vs_out.color = color;
}
