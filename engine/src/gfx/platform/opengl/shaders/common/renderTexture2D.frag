out vec4 color;
in vec2 uv0;

uniform sampler2D sampler0;

uniform int channel;

void main() {
  const vec4 tex = texture(sampler0, uv0);
  color = vec4((channel < 0) ? tex : vec4(tex[channel]));
}
