layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec3 vViewRay0;

uniform mat4 model;

void main() {
  // Position
  const vec4 worldPosition = model * vec4(position, 1.0);
  const vec4 viewPosition = view * worldPosition;
  const vec4 clipPosition = perspective * viewPosition;
  gl_Position = clipPosition;

  vViewRay0 = worldPosition.xyz + camPosition;
}
