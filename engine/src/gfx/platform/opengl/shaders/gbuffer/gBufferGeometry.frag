layout(location = 0) out vec4 diffuse;
layout(location = 1) out vec4 normalDepth;
layout(location = 2) out vec4 specular;

in vec2 gUV0;
in vec3 gWorldPosition0;
in vec3 gViewPosition0;
in vec3 gNormal0;
in vec3 gTangent0;
in vec4 gPosition0;
noperspective in vec3 gWireframeDistance0;

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

void main() {
  const mat3 TBN = calcTBN(gNormal0, gTangent0);

  // Parallax Mapping
  vec2 uv = gUV0;
  if (enableParallaxTexture > 0) {
    uv = calcParallaxMapping(parallaxTexture, uv, TBN, camPosition, gWorldPosition0);
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
    const float nearDistance = min(min(gWireframeDistance0[0], gWireframeDistance0[1]), gWireframeDistance0[2]);

    const float edgeIntensity1 = exp2(-(1.0 / 1.0) * nearDistance * nearDistance);
    const float edgeIntensity2 = exp2(-(1.0 / 20.0) * nearDistance * nearDistance);

    const vec3 lineColorInner = (edgeIntensity1 * vec3(1.0)) + ((1.0 - edgeIntensity1) * vec3(0.0));
    const vec3 lineColorOuter = (edgeIntensity2 * vec3(0.0)) + ((1.0 - edgeIntensity2) * diffuse.xyz);

    diffuse.xyz = lineColorInner + lineColorOuter;
  }

  // Normal Mapping + Linear Depth
  const float depth = length(gViewPosition0);
  normalDepth = vec4(gNormal0, depth);
  if (enableNormalTexture > 0) {
    const vec3 normalMap = calcNormalMapping(normalTexture, uv, TBN);
    normalDepth = vec4(normalMap, depth);
  }

  // Specular Mapping
  vec3 specularColorFinal = specularColor;
  const float specularShininessFinal = max(0.05, 0.9 - (log2(specularShininess) / 9.0));
  if (enableSpecularTexture > 0) {
    specularColorFinal = texture(specularTexture, uv).xyz;
  }
  specular = vec4(specularColorFinal, specularShininessFinal);
}
