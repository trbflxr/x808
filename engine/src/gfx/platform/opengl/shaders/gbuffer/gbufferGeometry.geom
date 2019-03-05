layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 v_uv0[];
in vec3 v_normal0[];
in vec3 v_tangent0[];
in vec4 v_position0[];
in vec3 v_worldPosition0[];

out vec2 g_uv0;
out vec3 g_normal0;
out vec3 g_tangent0;
out vec4 g_position0;
out vec3 g_worldPosition0;
noperspective out vec3 g_wireframeDistance0;

uniform int cullTest;
uniform vec2 renderSize;

const float wfScale = 1.2;

void main() {
  vec4[3] positions;
  vec2[3] wireframePoints;

  for (int i = 0; i < 3; ++i) {
    positions[i] = v_position0[i];
    wireframePoints[i] = (renderSize * wfScale) * v_position0[i].xy / v_position0[i].w;
  }

  vec2 v[3] = vec2[3](wireframePoints[2] - wireframePoints[1], wireframePoints[2] - wireframePoints[0],
                      wireframePoints[1] - wireframePoints[0]);
  float area = abs(v[1].x * v[2].y - v[1].y * v[2].x);

  vec3 chooser[3] = vec3[3](vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));

  bool cull = true;
  if (cullTest > 0) {
    cull = frustumCullTest(positions);
  }

  if (cull) {
    for (int i = 0; i < 3; ++i) {
      g_wireframeDistance0 = vec3(area / length(v[i])) * chooser[i];

      g_uv0 = v_uv0[i];
      g_normal0 = v_normal0[i];
      g_tangent0 = v_tangent0[i];
      g_position0 = v_position0[i];
      g_worldPosition0 = v_worldPosition0[i];

      gl_Position = v_position0[i];
      EmitVertex();
    }

    EndPrimitive();
  }
}
