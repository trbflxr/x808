R"(
in vec2 uv0;

out vec4 out_Color;

uniform vec2 blurScale;

//diffuse in this case = filterTexture
uniform sampler2D diffuse;

void main() {
  out_Color = vec4(0.0);

  out_Color += texture(diffuse, uv0 + (vec2(-3.0) * blurScale)) * (1.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(-2.0) * blurScale)) * (6.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(-1.0) * blurScale)) * (15.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(0.0) * blurScale)) * (20.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(1.0) * blurScale)) * (15.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(2.0) * blurScale)) * (6.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(3.0) * blurScale)) * (1.0 / 64.0);
}
)"
