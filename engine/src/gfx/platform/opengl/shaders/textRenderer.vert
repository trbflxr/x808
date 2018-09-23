layout(location = 0) in vec4 posTid;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 color;
layout(location = 3) in vec4 outlineColor;
layout(location = 4) in vec2 offset;
layout(location = 5) in vec4 widthEdge;

uniform mat4 projection;
uniform mat4 view;

out float tid0;
out vec2 uv0;
out vec4 color0;
out vec4 outlineColor0;
out vec2 offset0;
out vec4 widthEdge0;

void main() {
  gl_Position = (projection * view) * vec4(posTid.xyz, 1.0);

  tid0 = posTid.w;
  uv0 = uv;
  color0 = color;
  outlineColor0 = outlineColor;
  offset0 = offset;
  widthEdge0 = widthEdge;
}
