//
// Created by FLXR on 8/17/2018.
//

#include <xetools/spak.hpp>

int main(int argc, char **argv) {
	printf("src: %s\n", argv[1]);
	printf("dest: %s\n", argv[2]);

	xe::spak::pack(argv[1], argv[2]);

	return 0;
}
