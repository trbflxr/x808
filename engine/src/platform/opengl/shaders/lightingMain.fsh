R"(
void main() {
  out_Color = texture(diffuse, uv0.xy) * CalcLightingEffect(normal0, worldPos0);
}
)"
