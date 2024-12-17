#include "CommandOption.h"

namespace utils
{
	CommandOption::CommandOption(const std::string& id)
		: m_id(id), m_type(CommandOption::Type::FLAG), m_defaultValue(false)
	{
	}

	CommandOption::CommandOption(const std::string& id, CommandOption::Type type)
		: m_id(id), m_type(type), m_defaultValue(false)
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
		m_defaultValue = value;
		return *this;
	}

	CommandOption& CommandOption::setArgument(CommandArgument argument)
	{
		m_type = Type::FLAG;
		m_argument = argument.setRequired(true);
		return *this;
	}

	CommandOption& CommandOption::setDefaultArgumentValue(const std::string& value)
	{
		m_defaultArgumentValue = value;
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

	bool CommandOption::defaultValue() const
	{
		return m_defaultValue;
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

	std::string CommandOption::defaultArgumentValue() const
	{
		return m_defaultArgumentValue;
	}

	std::set<std::string> CommandOption::conflicts() const
	{
		return m_conflictIds;
	}
}
