#ifndef UTILS_CMD_COMMAND_OPTION_H
#define UTILS_CMD_COMMAND_OPTION_H

#include <string>
#include <vector>

namespace utils::cmd
{

	class CommandOption
	{
	public:
		enum OptionType
		{
			MESSAGE,
			FLAG,
			INT,
			FLOAT,
			STRING
		};

	public:
		CommandOption(const std::string& id, OptionType optionType);
		~CommandOption() = default;

		CommandOption* setLongFlag(const std::string& flag);
		CommandOption* setShortFlag(const std::string& flag);
		CommandOption* setHelp(const std::string& message);
		CommandOption* conflictsWith(const std::string& argId);

		std::string id();
		std::string longFlag();
		std::string shortFlag();
		std::string help();
		std::vector<std::string> conflicts();

	private:
		std::string m_id;
		std::string m_longFlag;
		std::string m_shortFlag;
		std::string m_helpMessage;
		std::vector<std::string> m_conflictIds;
	};
}

#endif // !UTILS_CMD_COMMAND_OPTION_H
