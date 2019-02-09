layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
in float tid0;

uniform sampler2D textures[@MAX_TEXTURES];

uniform vec3 lightColor;
uniform vec2 lightPosition;
uniform vec2 intensityDistance;

void main() {
  vec4 diffuse = color0;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);
      diffuse = texture(textures[tid], uv0);
  }

  vec3 ambient = vec3(0.5, 0.5, 0.5);

  vec2 lightDir = vec2(lightPosition.xy - gl_FragCoord.xy);
  float distance = 1.0 / length(lightPosition - gl_FragCoord.xy) * intensityDistance.x;

  float atten = 1.0 - length(lightDir) / intensityDistance.y;

  vec3 i = ambient + lightColor * atten;

  vec3 lf = vec3(distance * atten * lightColor);

  color = vec4(diffuse.xyz * lf, diffuse.a) * color0;
}
