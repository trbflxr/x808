out vec4 color;
in vec2 uv0;

uniform sampler2D sampler0;  // Diffuse
uniform sampler2D sampler1;  // Lighting
uniform sampler2D sampler2;  // Lighting - Specular

void main() {
  const vec3 ambient = vec3(0.1);
  const vec4 diffuseTexture = texture(sampler0, uv0);
  const vec3 lighting = texture(sampler1, uv0).xyz;
  const vec3 lightingSpecular = texture(sampler2, uv0).xyz;

  const int material = int(diffuseTexture.a);
  const vec3 diffuse = diffuseTexture.rgb;

  vec3 final = ((lighting + ambient) * diffuse) + lightingSpecular;

  // Normal Objects
  // Light Emitters
  const vec3[] materials = vec3[2](diffuse, final);

  final = materials[material];

  color = vec4(final, 1.0);
}
