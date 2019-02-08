layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in float tid;
layout(location = 3) in vec4 color;

uniform mat4 projection;
uniform mat4 view;

out vec2 uv0;
out vec4 color0;
out float tid0;

out vec4 position0;

void main() {
  uv0 = uv;
  tid0 = tid;
  color0 = color;
  position0 = view * position;

  gl_Position = projection * position0;
}
