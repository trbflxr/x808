layout(location = 0) out vec4 diffuse;
layout(location = 1) out vec4 specular;

in vec3 vViewRay0;

uniform sampler2D sampler0;         // Normal & Depth
uniform sampler2D sampler1;         // Specular
uniform samplerCubeArray sampler2;  // Shadow Depth

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float lightFalloff;

uniform int shadowId;

void main() {
  // Calculate Texture Coordinates
  const vec2 resolution = textureSize(sampler0, 0);
  const vec2 uv = gl_FragCoord.xy / resolution;

  const vec4 normalDepth = texture(sampler0, uv);
  const float depth = normalDepth.a;

  const vec3 worldPosition = calcWorldPosition(depth, vViewRay0, camPosition);

  const vec4 specularProperties = texture(sampler1, uv);

  vec3 L;
  vec4 tempDiffuse;
  vec4 tempSpecular;

  float visibility = 1.0;
  if (shadowId != -1) {
    // todo: calc shadow
  }

  calcLighting(uv, worldPosition, normalDepth.xyz, camPosition, lightPosition, lightColor, lightIntensity, lightFalloff,
               specularProperties, L, tempDiffuse, tempSpecular);

  diffuse = tempDiffuse * visibility;
  specular = tempSpecular * visibility;
}
