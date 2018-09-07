layout(location = 0) out vec4 diffuse;
layout(location = 1) out vec4 specular;

in vec3 vViewRay0;

uniform sampler2D sampler0;  // Normal & Depth
uniform sampler2D sampler1;  // Specular

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float lightFalloff;
uniform float lightSpotAngle;
uniform float lightSpotBlur;

void main() {
  // Calculate Texture Coordinates
  vec2 resolution = textureSize(sampler0, 0);
  vec2 uv = gl_FragCoord.xy / resolution;

  vec4 normalDepth = texture(sampler0, uv);
  float depth = normalDepth.a;

  vec3 worldPosition = calcWorldPosition(depth, vViewRay0, camPosition);

  vec4 specularProperties = texture(sampler1, uv);

  vec3 L;
  vec4 tempDiffuse;
  vec4 tempSpecular;

  calcLighting(uv, worldPosition, normalDepth.xyz, camPosition, lightPosition, lightColor, lightIntensity, lightFalloff,
               specularProperties, L, tempDiffuse, tempSpecular);

  float visibility = calcSpotLightCone(L, lightDirection, lightSpotAngle, lightSpotBlur);

  diffuse = tempDiffuse * visibility;
  specular = tempSpecular * visibility;
}
