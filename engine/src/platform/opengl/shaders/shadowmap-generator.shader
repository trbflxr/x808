R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;

uniform mat4 sys_MVP;

void main() { gl_Position = sys_MVP * position; }

#shader fragment
#version 330

out vec4 out_Color;

void main() {
  float depth = gl_FragCoord.z;

  float dx = dFdx(depth);
  float dy = dFdy(depth);
  float moment2 = depth * depth + 0.25 * (dx * dx + dy * dy);

  out_Color = vec4(depth, moment2, 0.0, 0.0);
}
)"
