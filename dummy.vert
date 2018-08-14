layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec2 uv0;

uniform mat4 MVP;

void main() {
  gl_Position = MVP * position;
  uv0 = uv;
}
