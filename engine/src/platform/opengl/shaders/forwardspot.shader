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

struct SpotLight {
  vec3 direction;
  float cutoff;
};

uniform vec3 sys_EyePos;
uniform sampler2D diffuse;

uniform float sys_SpecularIntensity;
uniform float sys_SpecularPower;

uniform PointLight sys_ActivePointLight;
uniform SpotLight sys_ActiveSpotLight;

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

vec4 calcPointLight(PointLight light, vec3 normal) {
  vec3 lightDirection = worldPos0 - light.position;
  float distanceToPoint = length(lightDirection);

  if (distanceToPoint > light.range) {
    return vec4(0, 0, 0, 0);
  }

  lightDirection = normalize(lightDirection);

  vec4 color = calcLight(light, lightDirection, normal);

  float attenuation = light.constant + light.linear * distanceToPoint +
                      light.exponent * distanceToPoint * distanceToPoint + 0.0001;

  return color / attenuation;
}

vec4 calcSpotLight(PointLight pointLight, SpotLight spotLight, vec3 normal) {
  vec3 lightDirection = normalize(worldPos0 - pointLight.position);
  float spotFactor = dot(lightDirection, spotLight.direction);

  vec4 color = vec4(0, 0, 0, 0);

  if (spotFactor > spotLight.cutoff) {
    color = calcPointLight(pointLight, normal) * (1.0 - (1.0 - spotFactor) / (1.0 - spotLight.cutoff));
  }

  return color;
}

void main() {
  color = texture(diffuse, uv0.xy) * calcSpotLight(sys_ActivePointLight, sys_ActiveSpotLight, normalize(normal0));
}

)"
