#ifndef UTILS_CMD_COMMAND_H
#define UTILS_CMD_COMMAND_H

#include <vector>
#include <string>
#include <map>
#include <optional>
#include <variant>

#include "CommandArgument.h"
#include "CommandOption.h"

namespace utils
{
	class Command
	{
	public:
		Command(int argc, const char* argv[]);
		~Command() = default;

		Command& setName(const std::string& name);
		Command& setVersion(const std::string& version);
		Command& setDescription(const std::string& description);
		Command& addArgument(CommandArgument argument);
		Command& addOption(CommandOption option);

		std::string getSingle(const std::string& id);
		std::vector<std::string> getMultiple(const std::string& id);
		bool getFlag(const std::string& id);

		void parse();

	private:
		std::string m_name;
		std::string m_version;
		std::string m_description;

		std::vector<std::string> m_commandArgs;
		int m_nextArgument;

		std::vector<CommandArgument> m_arguments;
		std::vector<CommandOption> m_options;

		std::map<std::string, std::string> m_singleValues;
		std::map<std::string, std::vector<std::string>> m_multipleArguments;
		std::map<std::string, bool> m_flagValues;

		std::string generateVersion() const;
		std::string generateHelp() const;

		void handleArgument(int i);
		void handleShortFlag(int i);
		void handleLongFlag(int i);

		CommandOption findOption(const std::string& longFlag);
		CommandOption findOption(char shortFlag);
	};
}

#endif // !UTILS_CMD_COMMAND_H