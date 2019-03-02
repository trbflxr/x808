layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 uv0;

void main() {
  gl_Position = vec4(position.x, position.y, 0.0, 1.0);
  uv0 = uv;
}
