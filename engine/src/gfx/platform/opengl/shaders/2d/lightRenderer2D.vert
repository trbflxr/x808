layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 color;
layout(location = 3) in int useTexture;
layout(location = 4) in int text;

uniform mat4 projection;
uniform mat4 view;

out vec2 uv0;
out vec4 color0;
out vec4 position0;
flat out int useTexture0;
flat out int text0;

void main() {
  gl_Position = (projection * view) * position;

  uv0 = uv;
  color0 = color;
  position0 = position * view;
  useTexture0 = useTexture;
  text0 = text;
}
