layout(location = 0) in vec2 position;

out vec2 uv0[11];
flat out int instanceID;

uniform int vertPass;
uniform vec2 targetSize;

vec2 data[3] = vec2[](vec2(-1.0, -1.0), vec2(3.0, -1.0), vec2(-1.0, 3.0));

void main() {
  float x = -1.0 + float((gl_VertexID & 1) << 2);
  float y = -1.0 + float((gl_VertexID & 2) << 1);
  vec2 cuv = vec2((x + 1.0) * 0.5, (y + 1.0) * 0.5);

  if (vertPass > 0) {
    float texelSize = 1.0 / targetSize.x;
    for (int i = -5; i < 5; ++i) {
      uv0[i + 5] = cuv + vec2(texelSize * float(i), 0.0);
    }
  } else {
    float texelSize = 1.0 / targetSize.y;
    for (int i = -5; i < 5; ++i) {
      uv0[i + 5] = cuv + vec2(0.0, texelSize * float(i));
    }
  }

  instanceID = gl_InstanceID;
  gl_Position = vec4(data[gl_VertexID], 0.0, 1.0);
}
