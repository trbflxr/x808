layout(location = 0) out vec4 color;

in vec2 uv0;
in vec4 color0;
in float tid0;
in vec4 position0;

struct Light {
  vec4 position;
  vec4 color;
};

layout (std140, binding = 2) uniform Lights {
  Light light[@MAX_PLIGHTS];
};

uniform vec3 ambient;
uniform int lightsSize;

uniform sampler2D textures[@MAX_TEXTURES];

void main() {
  vec4 diffuse = color0;

  if (tid0 > 0.0) {
    int tid = int(tid0 - 0.5);
    diffuse = texture(textures[tid], uv0);
  }

  vec3 acc = ambient;
  int size = lightsSize < @MAX_PLIGHTS ? lightsSize : @MAX_PLIGHTS;
  for (int i = 0; i < size; i++) {
    float distance = distance(light[i].position.xy, position0.xy);
    float d = 0.0;
    if(distance <= light[i].color.a){
      d = 1.0 - abs(distance / light[i].color.a);
    }

    acc += light[i].color.rgb * d;
  }

  color = vec4(diffuse.rgb * acc, diffuse.a);
}
