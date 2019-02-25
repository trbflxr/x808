//
// Created by FLXR on 2/25/2019.
//

#include <xetools/spak.hpp>
#include <libgen.h>
#include <cstring>

namespace xe {

	std::string spak::getFileName(const std::string &str, bool includeExt) {
		std::string temp = str;
		char *s = basename(temp.data());

		size_t size = strlen(s);

		if (!includeExt) {
			int lastDot = -1;

			for (size_t i = 0; i < size; ++i) {
				if (s[i] == '.') {
					lastDot = static_cast<int>(i);
				}
			}

			if (lastDot != -1) {
				s[lastDot] = '\0';
			}
		}

		return s;
	}

}