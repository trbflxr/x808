layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 3) in vec4 color;

uniform mat4 projection;
uniform mat4 view;

out vec4 color0;

void main() {
  gl_Position = (projection * view) * position;

  color0 = color;
}
