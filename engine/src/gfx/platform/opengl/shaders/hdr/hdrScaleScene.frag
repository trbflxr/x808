out vec4 color;
in vec2 uv0;

uniform sampler2D sampler0;  // Scene

layout(std430, binding = 0) buffer ex { vec2 exposure[]; };

void main() {
  const vec4 scene = texture(sampler0, uv0);

  float lumAvg = 0.05 / exposure[0].y;
  lumAvg = exp2(log2(lumAvg));

  vec3 final = scene.rgb;
  final *= lumAvg;

  color = vec4(final, 1.0);
}
