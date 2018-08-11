R"(
out vec4 color;

in vec2 uv0;

uniform int useFXAA;

uniform sampler2D sampler0;

vec3 unchartedToTonemap(vec3 x) {
  x = max(x, 0.0);

  /* DEFAULT
  float A = 0.15;		// Sholder Strength
  float B = 0.50;		// Linear Strength
  float C = 0.10;		// Linear Angle
  float D = 0.30;		// Toe Strength (default: 0.2)
  float E = 0.02;		// Toe Numerator
  float F = 0.30;		// Toe Denominator
  */

  float A = 0.22;  // Sholder Strength
  float B = 0.30;  // Linear Strength
  float C = 0.10;  // Linear Angle
  float D = 0.50;  // Toe Strength (default: 0.2)
  float E = 0.02;  // Toe Numerator
  float F = 0.30;  // Toe Denominator

  vec3 final = ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;

  return final;
}

void main() {
  vec3 scene;

  if (useFXAA > 0) {
    scene = fxaa(sampler0, uv0);
  } else {
    scene = texture(sampler0, uv0).xyz;
  }

  vec3 final = unchartedToTonemap(2.0 * scene);

  float W = 11.2;
  vec3 whiteScale = 1.0 / unchartedToTonemap(vec3(W));
  final *= whiteScale;

  float gamma = 1.3;
  vec3 gammaCorrection = vec3(1.0 / gamma);
  final = pow(final.xyz, gammaCorrection);

  color = vec4(final, 1.0);
}
)"
