#include "CommandOption.h"

namespace utils
{
	CommandOption::CommandOption(const std::string& id)
		: m_id(id), m_type(CommandOption::Type::FLAG)
	{
	}
	
	CommandOption& CommandOption::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}
	
	CommandOption& CommandOption::setArgument(const std::string& defaultValue)
	{
		m_type = Type::ARGUMENT;
		m_defaultValue = defaultValue;
		m_argument = CommandArgument(m_id).setRequired(true);
		return *this;
	}

	CommandOption& CommandOption::setMessage(const std::string& message)
	{
		m_type = Type::MESSAGE;
		return *this;
	}

	CommandOption& CommandOption::setShortFlag(char flag)
	{
		m_shortFlag = flag;
		return *this;
	}

	CommandOption& CommandOption::addConflict(const std::string& id)
	{
		m_conflictIds.insert(id);
		return *this;
	}

	CommandOption::Type CommandOption::type() const
	{
		return m_type;
	}

	std::string CommandOption::id() const
	{
		return m_id;
	}

	std::string CommandOption::description() const
	{
		return m_description;
	}

	std::string CommandOption::defaultValue() const
	{
		return m_defaultValue;
	}

	std::string CommandOption::message() const
	{
		return m_message;
	}

	char CommandOption::shortFlag() const
	{
		return m_shortFlag.value();
	}

	bool CommandOption::hasShortFlag() const
	{
		return m_shortFlag.has_value();
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
