R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec2 uv0;
out vec3 normal0;
out vec3 worldPos0;

uniform mat4 sys_Model;
uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = uv;
  normal0 = (sys_Model * vec4(normal, 0.0)).xyz;
  worldPos0 = (sys_Model * position).xyz;
}

#shader fragment
#version 330

in vec2 uv0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 color;

struct PointLight {
  vec4 color;
  float intensity;
  float constant;
  float linear;
  float exponent;
  vec3 position;
  float range;
};

uniform vec3 sys_EyePos;
uniform sampler2D diffuse;

uniform float sys_SpecularIntensity;
uniform float sys_SpecularPower;

uniform PointLight sys_ActivePointLight;

vec4 calcLight(PointLight light, vec3 direction, vec3 normal) {
  float diffuseFactor = dot(normal, -direction);

  vec4 diffuseColor = vec4(0, 0, 0, 0);
  vec4 specularColor = vec4(0, 0, 0, 0);

  if (diffuseFactor > 0) {
    diffuseColor = light.color * light.intensity * diffuseFactor;

    vec3 directionToEye = normalize(sys_EyePos - worldPos0);
    vec3 reflectDirection = normalize(reflect(direction, normal));

    float specularFactor = dot(directionToEye, reflectDirection);
    specularFactor = pow(specularFactor, sys_SpecularPower);

    if (specularFactor > 0) {
      specularColor = light.color * sys_SpecularIntensity * specularFactor;
    }
  }

  return diffuseColor + specularColor;
}

vec4 calcPointLight(PointLight activePointLight, vec3 normal) {
  vec3 lightDirection = worldPos0 - activePointLight.position;
  float distanceToPoint = length(lightDirection);

  if (distanceToPoint > activePointLight.range) {
    return vec4(0, 0, 0, 0);
  }

  lightDirection = normalize(lightDirection);

  vec4 color = calcLight(activePointLight, lightDirection, normal);

  float attenuation = activePointLight.constant + activePointLight.linear * distanceToPoint +
                      activePointLight.exponent * distanceToPoint * distanceToPoint + 0.0001;

  return color / attenuation;
}

void main() {
  color = texture(diffuse, uv0.xy) * calcPointLight(sys_ActivePointLight, normalize(normal0));
}
)"
