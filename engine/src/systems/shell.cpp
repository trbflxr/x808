//
// Created by FLXR on 11/14/2018.
//

#include <xe/systems/shell.hpp>

namespace xe {

	Shell::Shell() {
		createDefaultCommands();
	}

	Shell::~Shell() { }

	void Shell::input(Event &event) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Tilde) {
				string s = commands["hello"](false);
				wprintf(L"%s\n", s.c_str());
			}
		}
	}

	void Shell::processCommand(const string &command) {

	}

	bool Shell::addCommand(const string &command, const std::function<string(bool hint)> &callback) {
		return false;
	}

	void Shell::createDefaultCommands() {
		commands["hello"] = [=](bool hint) {
			if (hint) return "Prints 'Hello'.";
			return "Hello";
		};
	}

}