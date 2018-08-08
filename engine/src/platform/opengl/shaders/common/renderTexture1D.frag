R"(
	out vec4 color;

	in vec2 uv;

	uniform sampler1D sampler0;

	void main()	{
		vec4 tex = texture(sampler0, uv.x);
		color = tex;
	}
)"
