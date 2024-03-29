layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

uniform mat4 model;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0);
}
