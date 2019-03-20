out float ao;

in vec2 uv0;

uniform sampler2D sampler0;  // Normals
uniform sampler2D sampler1;  // Positions

const vec3 taps[16] = vec3[](
    vec3(-0.364452, -0.014985, -0.513535), vec3(0.004669, -0.445692, -0.165899), vec3(0.607166, -0.571184, 0.377880),
    vec3(-0.607685, -0.352123, -0.663045), vec3(-0.235328, -0.142338, 0.925718), vec3(-0.023743, -0.297281, -0.392438),
    vec3(0.918790, 0.056215, 0.092624), vec3(0.608966, -0.385235, -0.108280), vec3(-0.802881, 0.225105, 0.361339),
    vec3(-0.070376, 0.303049, -0.905118), vec3(-0.503922, -0.475265, 0.177892), vec3(0.035096, -0.367809, -0.475295),
    vec3(-0.316874, -0.374981, -0.345988), vec3(-0.567278, -0.297800, -0.271889), vec3(-0.123325, 0.197851, 0.626759),
    vec3(0.852626, -0.061007, -0.144475));

#define TAP_SIZE 0.1
#define NUM_TAPS 16
#define SCALE 2.0

void main() {
  vec3 viewPos = texture(sampler1, uv0).xyz;
  vec3 viewNorm = texture(sampler0, uv0).xyz;
  for (int i = 0; i < NUM_TAPS; i++) {
    vec3 offset = TAP_SIZE * taps[i];
    vec2 uvOffset = uv0 + offset.xy;
    vec3 posOffset = texture(sampler1, uvOffset.xy).xyz;

    vec3 diff = posOffset - viewPos;
    float distance = length(diff);
    vec3 diffnorm = normalize(diff);

    float occlusion = max(0.0, dot(viewNorm, diffnorm)) * SCALE / (1.0 + distance);
    ao += 1.0 - occlusion;
  }
  ao /= NUM_TAPS;
}
