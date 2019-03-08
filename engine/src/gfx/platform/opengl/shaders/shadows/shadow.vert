layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec4 v_worldPosition0;
flat out int id0;

uniform mat4 model;

void main() {
  v_worldPosition0 = model * vec4(position, 1.0);
  id0 = gl_InstanceID;
}
