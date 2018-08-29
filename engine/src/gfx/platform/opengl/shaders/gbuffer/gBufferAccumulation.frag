out vec4 color;
in vec2 uv0;

uniform sampler2D sampler0;  // Diffuse
uniform sampler2D sampler1;  // Lighting
uniform sampler2D sampler2;  // Lighting - Specular
uniform sampler2D sampler3;  // Lighting - Atmospheric
uniform sampler2D sampler4;  // Lighting - Indirect

void main() {
  // const vec3 ambient = vec3(0.0);
  const vec3 ambient = vec3(0.1);
  const vec4 diffuseTexture = texture(sampler0, uv0);
  const vec3 lighting = texture(sampler1, uv0).xyz;
  const vec3 lightingSpecular = texture(sampler2, uv0).xyz;
  const vec4 lightingAtmoshpere = texture(sampler3, uv0);
  const vec4 lightingIndirect = texture(sampler4, uv0);

  const int material = int(diffuseTexture.a);
  const vec3 diffuse = diffuseTexture.rgb;

  vec3 final = (((lighting + ambient) * diffuse) + lightingSpecular) + lightingIndirect.xyz;
  // final *= 1.0 - lightingIndirect.w;

  // Normal Objects
  // Light Emitters
  // Space
  const vec3[] materials = vec3[3](
      final + lightingAtmoshpere.rgb,
      diffuse,
      (diffuse * mix(vec3(0.0), vec3(1.0), max(1.0 - (lightingAtmoshpere.a * 7.0), 0.0))) + lightingAtmoshpere.rgb);

  // final = materials[material];
  final = materials[0];

  color = vec4(final, 1.0);
}
