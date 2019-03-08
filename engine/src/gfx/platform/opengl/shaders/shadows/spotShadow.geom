layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 v_worldPosition0[];
flat in int id0[];

out vec4 g_viewPosition0;

void main() {
  int id = id0[0];

  vec4 viewPositions[3];
  vec4 clipPositions[3];
  for (int i = 0; i < 3; ++i) {
    viewPositions[i] = spotShadows[id].view * v_worldPosition0[i];
    clipPositions[i] = spotShadows[id].projection * viewPositions[i];
  }

  bool cull = frustumCullTest(clipPositions);
  if (cull) {
    for (int i = 0; i < 3; ++i) {
      g_viewPosition0 = viewPositions[i];
      gl_Position = clipPositions[i];
      gl_Layer = id0[i];

      EmitVertex();
    }
    EndPrimitive();
  }
}
