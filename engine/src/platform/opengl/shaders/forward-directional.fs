R"(
uniform DirectionalLight sys_ActiveDirectionalLight;

vec4 CalcLightingEffect(vec3 normal, vec3 worldPos) {
  return CalcDirectionalLight(sys_ActiveDirectionalLight, normal, worldPos);
}
)"
