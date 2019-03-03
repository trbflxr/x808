layout(location = 0) out vec4 diffuse;
layout(location = 1) out vec4 normalDepth;
layout(location = 2) out vec4 specular;

in vec2 g_uv0;
in vec3 g_worldPosition0;
in vec3 g_viewPosition0;
in vec3 g_normal0;
in vec3 g_tangent0;
in vec4 g_position0;
noperspective in vec3 g_wireframeDistance0;

uniform int enableWireframe;

uniform int enableDiffuseTexture;
uniform sampler2D diffuseTexture;
uniform vec3 diffuseColor;
uniform float emissionStrength;

uniform int enableSpecularTexture;
uniform sampler2D specularTexture;
uniform vec3 specularColor;
uniform float specularShininess;

uniform int enableNormalTexture;
uniform sampler2D normalTexture;

uniform int enableParallaxTexture;
uniform sampler2D parallaxTexture;

uniform int enableDispTexture;
uniform sampler2D dispTexture;
uniform float displacementStrength;

void main() {
  mat3 TBN = calcTBN(g_normal0, g_tangent0);

  // Parallax Mapping
  vec2 uv = g_uv0;
  if (enableParallaxTexture > 0) {
    uv = calcParallaxMapping(parallaxTexture, uv, TBN, camPosition.xyz, g_worldPosition0);
  }

  // Diffuse Mapping + Material
  vec4 diffuseColorFinal = vec4(diffuseColor, 1.0);
  if (enableDiffuseTexture > 0) {
    diffuseColorFinal = texture(diffuseTexture, uv);
  }

  float material = 0.0;
  if (emissionStrength > 0.0) {
    material = 1.0;
    diffuseColorFinal.xyz *= emissionStrength;
  }
  diffuse = vec4(diffuseColorFinal.xyz, material);

  if (enableWireframe > 0) {
    float nearDistance = min(min(g_wireframeDistance0[0], g_wireframeDistance0[1]), g_wireframeDistance0[2]);

    float edgeIntensity1 = exp2(-(1.0 / 1.0) * nearDistance * nearDistance);
    float edgeIntensity2 = exp2(-(1.0 / 20.0) * nearDistance * nearDistance);

    vec3 lineColorInner = (edgeIntensity1 * vec3(1.0)) + ((1.0 - edgeIntensity1) * vec3(0.0));
    vec3 lineColorOuter = (edgeIntensity2 * vec3(0.0)) + ((1.0 - edgeIntensity2) * diffuse.xyz);

    diffuse.xyz = lineColorInner + lineColorOuter;
  }

  // Normal Mapping + Linear Depth
  float depth = length(g_viewPosition0);
  normalDepth = vec4(g_normal0, depth);
  if (enableNormalTexture > 0) {
    vec3 normalMap = calcNormalMapping(normalTexture, uv, TBN);
    normalDepth = vec4(normalMap, depth);
  }

  // Specular Mapping
  vec3 specularColorFinal = specularColor;
  float specularShininessFinal = max(0.05, 0.9 - (log2(specularShininess) / 9.0));
  if (enableSpecularTexture > 0) {
    specularColorFinal = texture(specularTexture, uv).xyz;
  }
  specular = vec4(specularColorFinal, specularShininessFinal);
}
