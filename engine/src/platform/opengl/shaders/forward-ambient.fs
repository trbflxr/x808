R"(
void main() {
  vec3 directionToEye = normalize(sys_EyePos - worldPos0);
  vec2 uv = CalcParallaxUV(dispMap, tbnMat0, directionToEye, uv0, sys_DispMapScale, sys_DispMapBias);

  out_Color = texture(diffuse, uv) * sys_Intensity * sys_Color;
}
)"
