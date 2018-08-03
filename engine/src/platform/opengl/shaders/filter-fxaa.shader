R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 uv0;

uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = vec2(uv.x, 1.0 - uv.y);
}

#shader fragment
#version 330

in vec2 uv0;

out vec4 out_Color;

uniform sampler2D diffuse;

uniform vec2 sys_inverseFilterTextureSize;
uniform float sys_fxaaSpanMax;
uniform float sys_fxaaReduceMin;
uniform float sys_fxaaReduceMul;

void main() {
  vec2 uvOffset = sys_inverseFilterTextureSize;

  vec3 luma = vec3(0.299, 0.587, 0.114);
  float lumaTL = dot(luma, texture2D(diffuse, uv0.xy + (vec2(-1.0, -1.0) * uvOffset)).xyz);
  float lumaTR = dot(luma, texture2D(diffuse, uv0.xy + (vec2(1.0, -1.0) * uvOffset)).xyz);
  float lumaBL = dot(luma, texture2D(diffuse, uv0.xy + (vec2(-1.0, 1.0) * uvOffset)).xyz);
  float lumaBR = dot(luma, texture2D(diffuse, uv0.xy + (vec2(1.0, 1.0) * uvOffset)).xyz);
  float lumaM = dot(luma, texture2D(diffuse, uv0.xy).xyz);

  vec2 dir;
  dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
  dir.y = ((lumaTL + lumaBL) - (lumaTR + lumaBR));

  float dirReduce = max((lumaTL + lumaTR + lumaBL + lumaBR) * (sys_fxaaReduceMul * 0.25), sys_fxaaReduceMin);
  float inverseDirAdjustment = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

  dir = min(vec2(sys_fxaaSpanMax, sys_fxaaSpanMax), max(vec2(-sys_fxaaSpanMax, -sys_fxaaSpanMax), dir * inverseDirAdjustment)) *
        uvOffset;

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
