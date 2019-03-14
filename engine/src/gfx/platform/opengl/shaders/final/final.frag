layout(location = 0) out vec4 color;

in vec2 uv0;

uniform sampler2D sampler0;

vec3 tonemapFilmic(vec3 color) {
  vec3 x = max(vec3(0.0), color - 0.004);
  return (x * (6.2 * x + 0.5)) / (x * (6.2 * x + 1.7) + 0.06);
}

vec3 acesFilm(vec3 x) {
  float a = 2.51;
  float b = 0.03;
  float c = 2.43;
  float d = 0.59;
  float e = 0.14;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

vec3 uncharted2Tonemap(vec3 x) {
  float A = 0.20;  // Sholder Strength
  float B = 0.10;  // Linear Strength
  float C = 0.10;  // Linear Angle
  float D = 0.60;  // Toe Strength (default: 0.2)
  float E = 0.02;  // Toe Numerator
  float F = 0.20;  // Toe Denominator
  return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
}

vec3 tonemapUncharted2(vec3 color) {
  float W = 11.2;
  float exposureBias = 2.0;
  vec3 curr = uncharted2Tonemap(exposureBias * color);
  vec3 whiteScale = 1.0 / uncharted2Tonemap(vec3(W));
  return curr * whiteScale;
}

vec3 simpleHDR(vec3 color) {
  float exposure = 2.2;
  float gamma = 1.0;
  vec3 mapped = vec3(1.0) - exp(-color * exposure);
  mapped = pow(mapped, vec3(1.0 / gamma));
  return mapped;
}

void main() {
  vec3 scene = texture(sampler0, uv0).xyz;

  color = vec4(simpleHDR(scene), 1.0);
  // color = vec4(tonemapFilmic(scene), 1.0);
  // color = vec4(acesFilm(scene), 1.0);
  // color = vec4(tonemapUncharted2(scene), 1.0);
  // color = vec4(scene, 1.0);
}
