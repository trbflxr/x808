in vec2 uv0;
out vec4 out_Color;

uniform vec4 color;
uniform float intensity;

uniform sampler2D diffuse;
uniform int useDiffuse;

void main() {
  vec4 texColor = vec4(0.0, 0.0, 0.0, 0.0);
  
  if(useDiffuse == 1) {
  	texColor = texture(diffuse, uv0);
  } else {
  	texColor = vec4(0.55, 0.55, 0.55, 1.0);
  }
	
  out_Color = texColor * intensity * color;
}
