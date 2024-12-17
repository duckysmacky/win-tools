#ifndef UTILS_CMD_COMMAND_H
#define UTILS_CMD_COMMAND_H

#include <vector>
#include <string>
#include <map>

#include "Argument.h"
#include "Option.h"

namespace cmd
{
	class Command
	{
	public:
		Command(int argc, const char* argv[]);
		~Command() = default;

		Command& setName(const std::string& name);
		Command& setVersion(const std::string& version);
		Command& setDescription(const std::string& description);
		Command& addArgument(Argument argument);
		Command& addOption(Option option);

		std::string getValue(const std::string& id) const;
		std::vector<std::string> getMultiple(const std::string& id) const;
		bool getFlag(const std::string& id) const;

		void parse();

	private:
		std::string m_name;
		std::string m_version;
		std::string m_description;

		std::vector<std::string> m_commandArgs;
		int m_nextArgument;

		std::vector<Argument> m_arguments;
		std::vector<Option> m_options;

		std::map<std::string, std::string> m_singleValues;
		std::map<std::string, std::vector<std::string>> m_multipleValues;
		std::map<std::string, bool> m_flagValues;

		std::string generateVersion() const;
		std::string generateHelp() const;

		void handleArgument(int i);
		void handleShortFlag(int i);
		void handleLongFlag(int i);
		void handleOption(const Option& option, int i);

		Option findOption(const std::string& longFlag);
		Option findOption(char shortFlag);
	};
}

#endif // !UTILS_CMD_COMMAND_H