#ifndef UTILS_CMD_COMMAND_OPTION_H
#define UTILS_CMD_COMMAND_OPTION_H

#include <string>
#include <set>
#include <variant>
#include <optional>

#include "CommandArgument.h"

namespace utils
{

	class CommandOption
	{
	public:
		enum Type
		{
			MESSAGE,
			FLAG
		};

	public:
		CommandOption(const std::string& id);
		CommandOption(const std::string& id, CommandOption::Type type);
		~CommandOption() = default;

		CommandOption& setDescription(const std::string& description);
		CommandOption& setShortFlag(char flag);
		CommandOption& setDefaultValue(bool value);
		CommandOption& setArgument(CommandArgument argument);
		CommandOption& setDefaultArgumentValue(const std::string& value);
		CommandOption& addConflict(const std::string& id);

		std::string id() const;
		std::string description() const;
		char shortFlag() const;
		bool defaultValue() const;
		bool hasShortFlag() const;
		bool hasArgument() const;
		Type type() const;
		CommandArgument argument() const;
		std::string defaultArgumentValue() const;
		std::set<std::string> conflicts() const;

	private:
		std::string m_id;
		std::string m_description;
		std::optional<char> m_shortFlag;
		bool m_defaultValue;
		std::optional<CommandArgument> m_argument;
		std::string m_defaultArgumentValue;
		Type m_type;
		std::set<std::string> m_conflictIds;
	};
}

#endif // !UTILS_CMD_COMMAND_OPTION_H
