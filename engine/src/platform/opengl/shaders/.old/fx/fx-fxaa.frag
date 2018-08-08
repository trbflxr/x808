R"(
in vec2 uv0;

out vec4 out_Color;

uniform sampler2D diffuse;

uniform vec2 inverseFilterTextureSize;
uniform float fxaaSpanMax;
uniform float fxaaReduceMin;
uniform float fxaaReduceMul;

void main() {
  vec2 uvOffset = inverseFilterTextureSize;

  vec3 luma = vec3(0.299, 0.587, 0.114);
  float lumaTL = dot(luma, texture2D(diffuse, uv0.xy + (vec2(-1.0, -1.0) * uvOffset)).xyz);
  float lumaTR = dot(luma, texture2D(diffuse, uv0.xy + (vec2(1.0, -1.0) * uvOffset)).xyz);
  float lumaBL = dot(luma, texture2D(diffuse, uv0.xy + (vec2(-1.0, 1.0) * uvOffset)).xyz);
  float lumaBR = dot(luma, texture2D(diffuse, uv0.xy + (vec2(1.0, 1.0) * uvOffset)).xyz);
  float lumaM = dot(luma, texture2D(diffuse, uv0.xy).xyz);

  vec2 dir;
  dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
  dir.y = ((lumaTL + lumaBL) - (lumaTR + lumaBR));

  float dirReduce = max((lumaTL + lumaTR + lumaBL + lumaBR) * (fxaaReduceMul * 0.25), fxaaReduceMin);
  float inverseDirAdjustment = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

  dir = min(vec2(fxaaSpanMax, fxaaSpanMax), max(vec2(-fxaaSpanMax, -fxaaSpanMax), dir * inverseDirAdjustment)) * uvOffset;

  vec3 result1 = (1.0 / 2.0) * (texture2D(diffuse, uv0.xy + (dir * vec2(1.0 / 3.0 - 0.5))).xyz +
                                texture2D(diffuse, uv0.xy + (dir * vec2(2.0 / 3.0 - 0.5))).xyz);

  vec3 result2 = result1 * (1.0 / 2.0) + (1.0 / 4.0) * (texture2D(diffuse, uv0.xy + (dir * vec2(0.0 / 3.0 - 0.5))).xyz +
                                                        texture2D(diffuse, uv0.xy + (dir * vec2(3.0 / 3.0 - 0.5))).xyz);

  float lumaMin = min(lumaM, min(min(lumaTL, lumaTR), min(lumaBL, lumaBR)));
  float lumaMax = max(lumaM, max(max(lumaTL, lumaTR), max(lumaBL, lumaBR)));
  float lumaResult2 = dot(luma, result2);

  if (lumaResult2 < lumaMin || lumaResult2 > lumaMax) {
    out_Color = vec4(result1, 1.0);
  } else {
    out_Color = vec4(result2, 1.0);
  }
}
)"
