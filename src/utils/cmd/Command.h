#ifndef UTILS_CMD_COMMAND_H
#define UTILS_CMD_COMMAND_H

#include <vector>
#include <string>

#include "CommandArgument.h"
#include "CommandOption.h"

namespace utils::cmd
{
	class Command
	{
	public:
		Command(const std::string& name);
		Command(const std::string& name, const std::string& version);
		~Command() = default;

		void parseArguments(int argc, const char* argv[]);

		void setVersion(const std::string& version);
		void setHelp(const std::string& helpMessage);

		void addArgument(const CommandArgument& argument);
		void addOption(const CommandOption& option);

		std::string name();
		std::string version();
		std::string help();

	private:
		std::string m_name;
		std::string m_version;
		std::string m_helpMessage;
		std::vector<CommandArgument> m_arguments;
		std::vector<CommandOption> m_options;
	};
}

#endif // !UTILS_CMD_COMMAND_H