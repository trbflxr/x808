layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
in vec4 position0;
flat in int useTexture0;
flat in int text0;

uniform vec3 ambient;
uniform int lightsSize;

uniform sampler2D sampler0;

void main() {
  vec4 diffuse = color0.bgra;

  if (text0 > 0) {
    diffuse = color0.bgra * texture(sampler0, uv0).a;
  } else if (useTexture0 > 0) {
    diffuse *= texture(sampler0, uv0);
  }

  vec3 acc = ambient;
  int size = lightsSize < MAX_PLIGHTS ? lightsSize : MAX_PLIGHTS;
  for (int i = 0; i < size; i++) {
    float distance = distance(light[i].position.xy, position0.xy);
    float d = 0.0;
    if (distance <= light[i].color.a) {
      d = 1.0 - abs(distance / light[i].color.a);
    }

    acc += light[i].color.rgb * d;
  }

  color = vec4(diffuse.rgb * acc, diffuse.a);
}
