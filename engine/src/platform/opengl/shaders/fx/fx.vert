R"(
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 uv0;

uniform mat4 MVP;

void main() {
  gl_Position = MVP * position;
  uv0 = vec2(uv.x, 1.0 - uv.y);
}
)"
