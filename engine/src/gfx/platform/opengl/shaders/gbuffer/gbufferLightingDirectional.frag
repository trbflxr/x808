layout(location = 0) out vec3 diffuse;
layout(location = 1) out vec4 specular;

uniform sampler2D sampler0;       // Normal
uniform sampler2D sampler1;       // Specular
uniform sampler2D sampler2;       // Position
uniform sampler2DArray sampler3;  // Shadow

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform int enableShadows;
uniform vec2 shadowTexelSize;

bool isInsideTexture(vec2 uv) { return !(uv.y < 0.0 || uv.y > 1.0 || uv.x < 0.0 || uv.x > 1.0); }

void main() {
  vec2 resolution = textureSize(sampler0, 0);
  vec2 uv = gl_FragCoord.xy / resolution;

  vec3 normal = texture(sampler0, uv).xyz;
  vec4 specularProperties = texture(sampler1, uv);
  vec3 worldPosition = texture(sampler2, uv).xyz;

  vec3 tempDiffuse;
  vec4 tempSpecular;

  float shadowFactor = 1.0;

#if SHADOW_QUALITY > 0
  if (enableShadows > 0) {
    vec4 viewPos = dirShadows.view * vec4(worldPosition, 1.0);
    float compare = viewPos.z;
    for (int i = 0; i < MAX_DIR_CASCADES; ++i) {
      vec2 suv = (dirShadows.projection[i] * viewPos).xy * 0.5 + 0.5;
      if (isInsideTexture(suv)) {
        shadowFactor = calcShadow(sampler3, suv, i, compare, shadowTexelSize);
        break;
      }
    }
  }
#endif

  calcLightingDirectional(worldPosition, normal, camPosition.xyz, lightDirection, lightColor, lightIntensity,
                          specularProperties, tempDiffuse, tempSpecular);

  diffuse = tempDiffuse * shadowFactor;
  specular = tempSpecular * shadowFactor;
}
