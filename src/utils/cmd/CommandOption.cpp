#include "CommandOption.h"

namespace utils
{
	CommandOption::CommandOption(const std::string& id)
		: m_id(id), m_type(CommandOption::Type::FLAG)
	{
	}

	CommandOption::CommandOption(const std::string& id, CommandOption::Type type)
		: m_id(id), m_type(type)
	{
	}

	CommandOption& CommandOption::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}
	
	CommandOption& CommandOption::setShortFlag(const std::string& flag)
	{
		m_shortFlag = flag;
		return *this;
	}

	CommandOption& CommandOption::setArgument(CommandArgument argument)
	{
		m_type = Type::FLAG;
		m_argument = argument.isRequired(true);
		return *this;
	}
	
	CommandOption& CommandOption::addConflict(const std::string& id)
	{
		m_conflictIds.insert(id);
		return *this;
	}

	std::string CommandOption::id() const
	{
		return m_id;
	}

	std::string CommandOption::description() const
	{
		return m_description;
	}

	std::string CommandOption::shortFlag() const
	{
		return m_shortFlag;
	}

	bool CommandOption::hasShortFlag() const
	{
		return !m_shortFlag.empty();
	}

	bool CommandOption::hasArgument() const
	{
		return m_argument.has_value();
	}

	CommandOption::Type CommandOption::type() const
	{
		return m_type;
	}

	std::optional<CommandArgument> CommandOption::argument() const
	{
		return m_argument;
	}

	std::set<std::string> CommandOption::conflicts() const
	{
		return m_conflictIds;
	}
}
