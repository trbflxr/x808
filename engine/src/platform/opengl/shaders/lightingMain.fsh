R"(
void main() {
  vec3 normal = normalize(tbnMat0 * (255.0 / 128.0 * texture(normalMap, uv0).xyz - 1.0));
  out_Color = texture(diffuse, uv0) * CalcLightingEffect(normal, worldPos0);
}
)"
