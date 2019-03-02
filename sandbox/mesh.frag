layout(location = 0) out vec4 color;

in vec2 uv0;
in vec3 normal0;
in mat3 tbn0;

uniform sampler2D sampler0;
uniform sampler2D sampler1;

void main() {
    color = texture(sampler0, uv0);
}
