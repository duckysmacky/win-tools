#include "CommandOption.h"

namespace utils
{
	CommandOption::CommandOption(const std::string& id)
		: m_id(id), m_type(CommandOption::Type::FLAG), m_value(false)
	{
	}

	CommandOption::CommandOption(const std::string& id, CommandOption::Type type)
		: m_id(id), m_type(type), m_value(false)
	{
	}

	CommandOption& CommandOption::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}
	
	CommandOption& CommandOption::setShortFlag(char flag)
	{
		m_shortFlag = flag;
		return *this;
	}

	CommandOption& CommandOption::setDefaultValue(bool value)
	{
		m_value = value;
		return *this;
	}

	CommandOption& CommandOption::setArgument(CommandArgument argument)
	{
		m_type = Type::FLAG;
		m_argument = argument.setRequired(true);
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

	char CommandOption::shortFlag() const
	{
		return m_shortFlag.value();
	}

	bool CommandOption::value() const
	{
		return m_value;
	}

	bool CommandOption::hasShortFlag() const
	{
		return m_shortFlag.has_value();
	}

	bool CommandOption::hasArgument() const
	{
		return m_argument.has_value();
	}

	CommandOption::Type CommandOption::type() const
	{
		return m_type;
	}

	CommandArgument CommandOption::argument() const
	{
		return m_argument.value();
	}

	std::set<std::string> CommandOption::conflicts() const
	{
		return m_conflictIds;
	}
}
