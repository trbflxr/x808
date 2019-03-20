out vec4 color;

uniform sampler2D sampler0;

in vec2 uv0[11];

void main() {
  color = vec4(0.0);
  color += texture(sampler0, uv0[0]) * 0.0093;
  color += texture(sampler0, uv0[1]) * 0.028002;
  color += texture(sampler0, uv0[2]) * 0.065984;
  color += texture(sampler0, uv0[3]) * 0.121703;
  color += texture(sampler0, uv0[4]) * 0.175713;
  color += texture(sampler0, uv0[5]) * 0.198596;
  color += texture(sampler0, uv0[6]) * 0.175713;
  color += texture(sampler0, uv0[7]) * 0.121703;
  color += texture(sampler0, uv0[8]) * 0.065984;
  color += texture(sampler0, uv0[9]) * 0.028002;
  color += texture(sampler0, uv0[10]) * 0.0093;
}
