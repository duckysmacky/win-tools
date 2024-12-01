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
		CommandOption& setShortFlag(const std::string& flag);
		CommandOption& setArgument(CommandArgument argument);
		CommandOption& addConflict(const std::string& id);

		std::string id() const;
		std::string description() const;
		std::string shortFlag() const;
		bool hasShortFlag() const;
		bool hasArgument() const;
		Type type() const;
		std::optional<CommandArgument> argument() const;
		std::set<std::string> conflicts() const;

	private:
		std::string m_id;
		std::string m_description;
		std::string m_shortFlag;
		std::optional<CommandArgument> m_argument;
		Type m_type;
		std::set<std::string> m_conflictIds;
	};
}

#endif // !UTILS_CMD_COMMAND_OPTION_H
