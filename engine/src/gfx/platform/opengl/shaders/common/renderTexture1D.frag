out vec4 color;
in vec2 uv0;

uniform sampler1D sampler0;

void main(){
	color = texture(sampler0, uv0.x);
}
