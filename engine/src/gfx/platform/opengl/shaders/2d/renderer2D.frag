layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
flat in int useTexture0;
flat in int text0;

uniform sampler2D sampler0;

void main() {
  if (text0 > 0) {
    color = color0.bgra * texture(sampler0, uv0).a;
    return;
  }

  vec4 final = color0.bgra;

  if (useTexture0 > 0) {
    final *= texture(sampler0, uv0);
  }

  color = final;
}
