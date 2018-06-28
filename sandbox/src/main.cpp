#include <math/math.hpp>
#include <cstdio>

int main() {
	xe::vec2u v1(2,2);
	xe::vec2u v2(1,1);
	xe::vec2u v3 = v1 + v2;

	printf("x: %u, y: %u\n", v1.x, v1.y);
	printf("x: %u, y: %u\n", v2.x, v2.y);
	printf("x: %u, y: %u\n", v3.x, v3.y);


	return 0;
}