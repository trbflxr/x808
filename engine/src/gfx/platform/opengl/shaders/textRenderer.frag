layout(location = 0) out vec4 color;

in float tid0;
in vec2 uv0;
in vec4 color0;
in vec4 outlineColor0;
in vec2 offset0;
in vec4 widthEdge0;

uniform sampler2D textures[@MAX_TEXTURES];

void main() {
  vec4 final = color0;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);

    float distance0 = 1.0 - texture(textures[tid], uv0).a;
    float alpha0 = 1.0 - smoothstep(widthEdge0.x, widthEdge0.x + widthEdge0.y, distance0);

    float totalAlpha = alpha0;
    vec3 totalColor = color0.rgb;

    if (widthEdge0.w > 0.005) {
      float distance1 = 1.0 - texture(textures[tid], uv0 + offset0).a;
      float alpha1 = 1.0 - smoothstep(widthEdge0.z, widthEdge0.z + widthEdge0.w, distance1);

      totalAlpha = totalAlpha + (1.0 - alpha0) * alpha1;
      totalColor = mix(outlineColor0.rgb, totalColor, alpha0 / totalAlpha);
    }

    final = vec4(totalColor, totalAlpha) * color0.a;
  }

  color = final;
}
