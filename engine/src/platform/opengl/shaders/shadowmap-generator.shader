R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;

uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
}

#shader fragment
#version 330

out vec4 out_Color;

void main() {
  out_Color = vec4(gl_FragCoord.z);
}
)"
