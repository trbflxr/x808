layout(location = 0) out vec2 depth;

in vec4 position0;

void main() {
  float d = position0.z;

  float dx = dFdx(d);
  float dy = dFdy(d);

  depth.x = d;
  depth.y = d * d + 0.25 * (dx * dx + dy * dy);
}
