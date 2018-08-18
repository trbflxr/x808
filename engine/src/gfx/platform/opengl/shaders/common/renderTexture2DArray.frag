out vec4 color;
in vec2 uv0;

uniform sampler2DArray sampler0;
uniform int layer;

void main() {
	color = texture(sampler0, vec3(uv0, layer));
}
