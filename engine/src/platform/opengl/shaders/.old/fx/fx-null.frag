R"(
in vec2 uv0;

out vec4 out_Color;

uniform sampler2D diffuse;

void main() {
    out_Color = texture(diffuse, uv0);
}
)"
