//
// Created by FLXR on 11/14/2018.
//

#ifndef X808_SHELL_HPP
#define X808_SHELL_HPP


#include <map>
#include <functional>
#include <xe/systems/system.hpp>

namespace xe {

	class Shell : public System {
	public:
		explicit Shell();
		~Shell() override;

		void input(Event &event) override;

		void processCommand(const string &command);

		bool addCommand(const string &command, const std::function<string(bool hint)> &callback);

	private:
		void createDefaultCommands();

	private:


		string base = "xe> ";

		std::map<string, std::function<string(bool hint)>> commands;
	};

}


#endif //X808_SHELL_HPP
