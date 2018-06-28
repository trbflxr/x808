#include <math/math.hpp>
#include <cstdio>

int main() {
	xe::vec2 v1(1, 1);
	xe::vec2 v2(1, 1);

	xe::vec2 v3 = v1 + v2;

	printf("x: %.2f, y: %.2f\n", v1.x, v1.y);
	printf("x: %.2f, y: %.2f\n", v2.x, v2.y);
	printf("x: %.2f, y: %.2f\n", v3.x, v3.y);

	printf("%i\n", v1 < v3);

	return 0;
}