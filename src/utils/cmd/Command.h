#ifndef UTILS_CMD_COMMAND_H
#define UTILS_CMD_COMMAND_H

#include <vector>
#include <string>
#include <map>

#include "CommandArgument.h"
#include "CommandOption.h"

namespace utils
{
	class Command
	{
	public:
		Command(const std::string& name, const std::string& version);
		~Command() = default;

		void parseArguments(int argc, const char* argv[]);

		Command& setDescription(const std::string& description);
		Command& addArgument(CommandArgument argument);
		Command& addOption(CommandOption option);

	private:
		std::string m_name;
		std::string m_version;
		std::string m_description;
		std::vector<CommandArgument> m_arguments;
		std::vector<CommandOption> m_options;
		//std::map<std::string, CommandOption*> m_longOptions;
		//std::map<std::string, CommandOption*> m_shortOptions;

		std::string generateVersion() const;
		std::string generateHelp() const;
	};
}

#endif // !UTILS_CMD_COMMAND_H