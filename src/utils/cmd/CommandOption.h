#ifndef UTILS_CMD_COMMAND_OPTION_H
#define UTILS_CMD_COMMAND_OPTION_H

#include <string>
#include <optional>
#include <set>

#include "CommandArgument.h"

namespace utils
{

	class CommandOption
	{
	public:
		enum Type
		{
			MESSAGE,
			FLAG,
			ARGUMENT
		};

	public:
		CommandOption(const std::string& id);
		~CommandOption() = default;

		CommandOption& setDescription(const std::string& description);
		CommandOption& setArgument(const std::string& defaultValue);
		CommandOption& setMessage(const std::string& message);
		CommandOption& setShortFlag(char flag);
		CommandOption& addConflict(const std::string& id);

		Type type() const;
		std::string id() const;
		std::string description() const;
		std::string defaultValue() const;
		std::string message() const;
		char shortFlag() const;
		bool hasShortFlag() const;
		CommandArgument argument() const;
		std::set<std::string> conflicts() const;

	private:
		Type m_type;
		std::string m_id;
		std::string m_description;
		std::string m_defaultValue;
		std::string m_message;
		std::optional<char> m_shortFlag;
		std::optional<CommandArgument> m_argument;
		std::set<std::string> m_conflictIds;
	};
}

#endif // !UTILS_CMD_COMMAND_OPTION_H
