layout(location = 0) out vec2 depth;

in vec4 g_viewPosition0;

void main() {
  float d = g_viewPosition0.z;

  float dx = dFdx(d);
  float dy = dFdy(d);

  depth = vec2(d, d * d + 0.25 * (dx * dx + dy * dy));
}
