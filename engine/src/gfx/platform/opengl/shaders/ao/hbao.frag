out float ao;

in vec2 uv0;

uniform sampler2D sampler0;  // Normals
uniform sampler2D sampler1;  // Depth

uniform mat4 invProj;

#define SAMPLING_RADIUS 0.5
#define NUM_SAMPLING_DIRECTIONS 8

#define SAMPLING_STEP 0.004
#define NUM_SAMPLING_STEPS 4
#define TANGENT_BIAS 0.2
#define SCALE 2.0

void main() {
  float startZ = texture(sampler1, uv0).r;
  vec3 startPos = vec3(uv0, startZ);
  vec3 normPos = startPos * 2.0 - 1.0;

  vec4 unproject = invProj * vec4(normPos, 1.0);
  vec3 viewPos = unproject.xyz / unproject.w;
  vec3 viewNorm = texture(sampler0, uv0).xyz;

  float total = 0.0;
  float d = 2.0 * MATH_PI / NUM_SAMPLING_DIRECTIONS;
  for (int i = 0; i < NUM_SAMPLING_DIRECTIONS; ++i) {
    float samplingAngle = i * d;
    vec2 sampleDir = vec2(cos(samplingAngle), sin(samplingAngle));

    float tangentAngle = acos(dot(vec3(sampleDir, 0), viewNorm)) - (0.5 * MATH_PI) + TANGENT_BIAS;
    float horizonAngle = tangentAngle;

    vec3 lastDiff = vec3(0);
    for (int j = 0; j < NUM_SAMPLING_STEPS; ++j) {
      vec2 sampleOffset = float(j + 1.0) * SAMPLING_STEP * sampleDir;
      vec2 offsetUV = uv0 + sampleOffset;

      float offsetStartZ = texture(sampler1, offsetUV).r;
      vec3 offsetStartPos = vec3(offsetUV, offsetStartZ);
      vec3 offsetNormPos = (2.0 * offsetStartPos) - 1.0;
      vec4 offsetUnprojec = invProj * vec4(offsetNormPos, 1.0);
      vec3 offsetViewPos = offsetUnprojec.xyz / offsetUnprojec.w;

      vec3 diff = offsetViewPos.xyz - viewPos.xyz;
      if (length(diff) < SAMPLING_RADIUS) {
        lastDiff = diff;
        float elevationAngle = atan(diff.z / length(diff.xy));
        horizonAngle = max(horizonAngle, elevationAngle);
      }
    }

    float attenuation = 1.0 / (1.0 + length(lastDiff));
    float occlusion = clamp(attenuation * (sin(horizonAngle) - sin(tangentAngle)) * SCALE, 0.0, 1.0);
    total += 1.0 - occlusion;
  }
  total /= NUM_SAMPLING_DIRECTIONS;

  ao = total;
}
