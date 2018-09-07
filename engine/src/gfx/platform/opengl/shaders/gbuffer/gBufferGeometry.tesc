layout(vertices = 3) out;

in vec3 vWorldPosition0[];
in vec2 vUV0[];
in vec3 vNormal0[];
in vec3 vTangent0[];

out vec3 tcWorldPosition0[];
out vec2 tcUV0[];
out vec3 tcNormal0[];
out vec3 tcTangent0[];

uniform int enableDispTexture;
uniform vec2 renderSize;
uniform int cullTest;

float screenSphereSize(vec4 e1, vec4 e2) {
  vec4 p1 = (e1 + e2) * 0.5;
  vec4 p2 = p1;
  p2.y += distance(e1, e2);

  p1 = p1 / p1.w;
  p2 = p2 / p2.w;

  float l = length((p1.xy - p2.xy) * renderSize * 0.5);

  return (clamp(l / 15.0, 1.0, 64.0));
}

void controlTessellation(mat4 vp, vec3[gl_MaxPatchVertices] worldPosition, vec3 normal) {
  vec4 vertexPosition[3];

  for (int i = 0; i < 3; i++) {
    vertexPosition[i] = vp * vec4(worldPosition[i], 1.0);
  }

  bool cull = true;
  if (cullTest > 0) {
    cull = frustumCullTest(vertexPosition) && backfaceCullTest(worldPosition[gl_InvocationID], -camPosition, normal);
  }

  if (cull) {
    if (enableDispTexture > 0) {
      gl_TessLevelOuter[2] = 1.0;
      gl_TessLevelOuter[1] = 1.0;
      gl_TessLevelOuter[0] = 1.0;
      gl_TessLevelInner[0] = 1.0;
    } else {
      // Calculate the tessellation levels
      gl_TessLevelOuter[2] = screenSphereSize(vertexPosition[1], vertexPosition[0]);
      gl_TessLevelOuter[1] = screenSphereSize(vertexPosition[2], vertexPosition[0]);
      gl_TessLevelOuter[0] = screenSphereSize(vertexPosition[2], vertexPosition[1]);
      gl_TessLevelInner[0] = max(gl_TessLevelOuter[1], max(gl_TessLevelOuter[0], gl_TessLevelOuter[2]));
    }
  } else {
    gl_TessLevelOuter[2] = 0.0;
    gl_TessLevelOuter[1] = 0.0;
    gl_TessLevelOuter[0] = 0.0;
    gl_TessLevelInner[0] = 0.0;
  }
}

void main() {
  tcWorldPosition0[gl_InvocationID] = vWorldPosition0[gl_InvocationID];
  tcUV0[gl_InvocationID] = vUV0[gl_InvocationID];
  tcNormal0[gl_InvocationID] = vNormal0[gl_InvocationID];
  tcTangent0[gl_InvocationID] = vTangent0[gl_InvocationID];

  controlTessellation(perspective * view, vWorldPosition0, vNormal0[gl_InvocationID]);
}
