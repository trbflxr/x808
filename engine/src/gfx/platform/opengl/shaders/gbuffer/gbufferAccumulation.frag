layout(location = 0) out vec4 color;

in vec2 uv0;

uniform sampler2D sampler0;  // Diffuse
uniform sampler2D sampler1;  // Lighting
uniform sampler2D sampler2;  // Lighting - Specular

uniform vec3 ambient;

void main() {
  vec4 diffuseTexture = texture(sampler0, uv0);
  vec3 lighting = texture(sampler1, uv0).xyz;
  vec3 lightingSpecular = texture(sampler2, uv0).xyz;

  int material = int(diffuseTexture.a);
  vec3 diffuse = diffuseTexture.rgb;

  vec3 final = ((lighting + ambient) * diffuse) + lightingSpecular;

  // Normal Objects
  // Light Emitters
  vec3[] materials = vec3[2](diffuse, final);

  final = materials[material];

  color = vec4(final, 1.0);
}
