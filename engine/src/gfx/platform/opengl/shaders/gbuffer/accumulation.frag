layout(location = 0) out vec4 color;

in vec2 uv0;

uniform sampler2D sampler0;  // position
uniform sampler2D sampler1;  // normal
uniform sampler2D sampler2;  // albedo

uniform int ambientPass;
uniform vec3 ambient;

void main() {
  vec3 diffuse = vec3(0.0f);

  if (ambientPass > 0) {
    diffuse += texture(sampler2, uv0).rgb * ambient;
  } else {
    // shadow casters

  }

  // diffuse += texture(sampler2, uv0).rgb;

  color = vec4(diffuse, 1.0);
  color *= min(100.0 / length(texture(sampler0, uv0).rgb), 1.0);
}
