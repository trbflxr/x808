layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec4 position0;

uniform mat4 model;

void main() {
  position0 = view * model * vec4(position, 1.0);
  gl_Position = projection * position0;
}
