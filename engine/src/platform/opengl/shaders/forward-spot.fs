R"(
uniform SpotLight sys_ActiveSpotLight;
uniform PointLight sys_ActivePointLight;

vec4 CalcLightingEffect(vec3 normal, vec3 worldPos) {
  return CalcSpotLight(sys_ActivePointLight, sys_ActiveSpotLight, normal, worldPos);
}
)"
