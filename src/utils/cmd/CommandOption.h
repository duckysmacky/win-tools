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
			FLAG,
			VALUE
		};

	public:
		CommandOption(const std::string& id);
		CommandOption(const std::string& id, CommandOption::Type type);
		~CommandOption() = default;

		CommandOption& setLongFlag(const std::string& flag);
		CommandOption& setShortFlag(const std::string& flag);
		CommandOption& setDescription(const std::string& message);
		CommandOption& conflictsWith(const std::string& id);
		CommandOption& addArgument(CommandArgument argument);

		std::string id() const;
		std::string longFlag() const;
		std::string shortFlag() const;
		std::string description() const;
		bool hasLongFlag() const;
		bool hasShortFlag() const;
		CommandOption::Type type() const;
		std::set<std::string> conflicts() const;

	private:
		std::string m_id;
		std::string m_longFlag;
		std::string m_shortFlag;
		std::string m_description;
		CommandOption::Type m_type;
		std::set<std::string> m_conflicts;
		std::optional<CommandArgument> m_argument;
		std::variant<bool, int, std::string> m_value;
	};
}

#endif // !UTILS_CMD_COMMAND_OPTION_H
