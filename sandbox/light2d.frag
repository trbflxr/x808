layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
in float tid0;

uniform sampler2D textures[@MAX_TEXTURES];

uniform vec3 lightColor;
uniform vec2 lightPosition;
uniform vec2 intensityDistance;
uniform vec3 ambient;

void main() {
  vec4 diffuse = color0;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);
    diffuse = texture(textures[tid], uv0);
  }

  float distance = distance(lightPosition.xy, gl_FragCoord.xy);
  float d = 0.0;
  if(distance <= intensityDistance.x){
    d = 1.0 - abs(distance / intensityDistance.x);
  }

  color = min(diffuse* ((vec4(lightColor * d, 1.0)) + vec4(ambient, 1.0)), diffuse);
}
