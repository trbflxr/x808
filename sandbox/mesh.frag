layout(location = 0) out vec4 color;

in vec2 uv0;

uniform sampler2D sampler0;

void main() {
    color = texture(sampler0, uv0);
}
