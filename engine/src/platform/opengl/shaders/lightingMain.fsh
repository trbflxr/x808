R"(
bool inRange(float val) { return val >= 0.0 && val <= 1.0; }

float CalcShadowAmount(sampler2D shadowMap, vec4 initialshadowMapUV) {
  vec3 shadowMapUV = initialshadowMapUV.xyz / initialshadowMapUV.w;

  if (inRange(shadowMapUV.x) && inRange(shadowMapUV.y) && inRange(shadowMapUV.z)) {
    return SampleVarianceShadowMap(shadowMap, shadowMapUV.xy, shadowMapUV.z, sys_shadowVarianceMin,
                                   sys_shadowLightBleedingReduction);
  } else {
    return 1.0;
  }
}

void main() {
  vec3 directionToEye = normalize(sys_EyePos - worldPos0);
  vec2 uv = CalcParallaxUV(dispMap, tbnMat0, directionToEye, uv0, sys_DispMapScale, sys_DispMapBias);
  vec3 normal = normalize(tbnMat0 * (255.0 / 128.0 * texture(normalMap, uv).xyz - 1.0));

  vec4 lightingAmt = CalcLightingEffect(normal, worldPos0) * CalcShadowAmount(shadowMap, shadowMapUV0);
  out_Color = texture(diffuse, uv) * lightingAmt;
}
)"
