layout(location = 0) out vec3 diffuse;
layout(location = 1) out vec4 specular;

uniform sampler2D sampler0;  // Normal
uniform sampler2D sampler1;  // Specular
uniform sampler2D sampler2;  // Position

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float lightFalloff;

void main() {
  vec2 resolution = textureSize(sampler0, 0);
  vec2 uv = gl_FragCoord.xy / resolution;

  vec3 normal = texture(sampler0, uv).xyz;
  vec4 specularProperties = texture(sampler1, uv);
  vec3 worldPosition = texture(sampler2, uv).xyz;

  vec3 L;
  vec3 tempDiffuse;
  vec4 tempSpecular;

  calcLighting(worldPosition, normal, camPosition.xyz, lightPosition, lightColor, lightIntensity, lightFalloff,
               specularProperties, L, tempDiffuse, tempSpecular);

  diffuse = tempDiffuse;
  specular = tempSpecular;
}
