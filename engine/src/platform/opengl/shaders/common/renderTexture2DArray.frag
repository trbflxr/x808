R"(
out vec4 color;

in vec2 uv;

uniform sampler2DArray sampler0;
uniform int layer;

void main() {
  vec4 tex = texture(sampler0, vec3(uv, layer));
  color = tex;
}
)"
