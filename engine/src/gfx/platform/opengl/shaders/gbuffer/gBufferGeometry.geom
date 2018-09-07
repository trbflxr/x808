layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 teNormal0[];
in vec3 teTangent0[];
in vec3 teWorldPosition0[];
in vec2 teUV0[];

out vec3 gNormal0;
out vec3 gTangent0;
out vec3 gViewPosition0;
out vec3 gWorldPosition0;
out vec2 gUV0;
out vec4 gPosition0;
noperspective out vec3 gWireframeDistance0;

// uniform vec2 renderSize;

void main() {
  vec4[3] viewPositions;
  vec4[3] clipPositions;
  vec2[3] wireframePoints;

  for (int i = 0; i < 3; i++) {
    viewPositions[i] = view * gl_in[i].gl_Position;
    clipPositions[i] = perspective * viewPositions[i];

    // todo: use render size
    wireframePoints[i] = vec2(1200) * clipPositions[i].xy / clipPositions[i].w;
  }

  vec2 v[3] = vec2[3](wireframePoints[2] - wireframePoints[1], wireframePoints[2] - wireframePoints[0],
                      wireframePoints[1] - wireframePoints[0]);
  float area = abs(v[1].x * v[2].y - v[1].y * v[2].x);

  vec3 chooser[3] = vec3[3](vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));

  // Output triangle
  for (int i = 0; i < 3; i++) {
    gWireframeDistance0 = vec3(area / length(v[i])) * chooser[i];
    gWorldPosition0 = teWorldPosition0[i];
    gViewPosition0 = viewPositions[i].xyz;
    gPosition0 = clipPositions[i];
    gTangent0 = teTangent0[i];
    gUV0 = teUV0[i];
    gNormal0 = teNormal0[i];

    gl_Position = clipPositions[i];
    EmitVertex();
  }

  EndPrimitive();
}
