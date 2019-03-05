layout(location = 0) out vec2 depth;

in vec4 position0;

uniform int rawZ;

void main() {
  float d = 0.0;
  if (rawZ > 0) {
    d = position0.z;
  } else {
    d = length(position0.xyz);
  }

  depth.x = d;

  // Compute partial derivatives of depth.
  float dx = dFdx(d);
  float dy = dFdy(d);
  // Compute second moment over the pixel extents.
  depth.y = d * d + 0.25 * (dx * dx + dy * dy);
}
