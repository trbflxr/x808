layout(triangles, fractional_odd_spacing, ccw) in;

in vec3 tcWorldPosition0[];
in vec2 tcUV0[];
in vec3 tcNormal0[];
in vec3 tcTangent0[];

out vec3 teWorldPosition0;
out vec2 teUV0;
out vec3 teNormal0;
out vec3 teTangent0;

uniform sampler2D dispTexture;
uniform int enableDispTexture;
uniform float displacementStrength = 0.1;

vec2 interpolate2DTriangle(const vec2 v0, const vec2 v1, const vec2 v2) {
  return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3DTriangle(const vec3 v0, const vec3 v1, const vec3 v2) {
  return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

vec4 interpolate3DTriangle(const vec4 v0, const vec4 v1, const vec4 v2) {
  return vec4(gl_TessCoord.x) * v0 + vec4(gl_TessCoord.y) * v1 + vec4(gl_TessCoord.z) * v2;
}

vec2 interpolate2DQuad(const vec2 v0, const vec2 v1, const vec2 v2, const vec2 v3) {
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  vec2 a = mix(v0, v1, u);
  vec2 b = mix(v2, v3, u);
  return mix(a, b, v);
}

vec3 interpolate3DQuad(const vec3 v0, const vec3 v1, const vec3 v2, const vec3 v3) {
  const float u = gl_TessCoord.x;
  const float v = gl_TessCoord.y;

  const vec3 a = mix(v0, v1, u);
  const vec3 b = mix(v2, v3, u);
  return mix(a, b, v);
}

void main() {
  teWorldPosition0 = interpolate3DTriangle(tcWorldPosition0[0], tcWorldPosition0[1], tcWorldPosition0[2]);
  teUV0 = interpolate2DTriangle(tcUV0[0], tcUV0[1], tcUV0[2]);
  teNormal0 = normalize(interpolate3DTriangle(tcNormal0[0], tcNormal0[1], tcNormal0[2]));
  teTangent0 = normalize(interpolate3DTriangle(tcTangent0[0], tcTangent0[1], tcTangent0[2]));

  if (enableDispTexture > 0) {
    const float displacement = texture(dispTexture, teUV0).r * displacementStrength;
    const vec3 displacementMod = teNormal0 * displacement;
    teWorldPosition0 += displacementMod;
  }

  gl_Position = vec4(teWorldPosition0, 1.0);
}
