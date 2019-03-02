layout(location = 0) out vec4 position;
layout(location = 1) out vec4 normal;
layout(location = 2) out vec4 color;

in vec3 position0;
in vec3 normal0;
in vec2 uv0;
in mat3 tbn0;

uniform sampler2D sampler0;  // diffuse
uniform sampler2D sampler1;  // specular
uniform sampler2D sampler2;  // normal

void main() {
  position = vec4(position0, 1.0);

  vec3 n = normalize(normal0);
  n = texture(sampler2, uv0).rgb;
  n = normalize(n * 2.0 - 1.0);
  n = normalize(tbn0 * n);

  normal = vec4(n, 1.0);

  color.rgb = texture(sampler0, uv0).rgb;
  color.a = texture(sampler1, uv0).r;
}
