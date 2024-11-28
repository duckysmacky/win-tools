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

	CommandOption& CommandOption::setLongFlag(const std::string& flag)
	{
		m_longFlag = flag;
		return *this;
	}

	CommandOption& CommandOption::setShortFlag(const std::string& flag)
	{
		m_shortFlag = flag;
		return *this;
	}

	CommandOption& CommandOption::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}

	CommandOption& CommandOption::conflictsWith(const std::string& id)
	{
		m_conflicts.insert(id);
		return *this;
	}

	CommandOption& CommandOption::addArgument(CommandArgument argument)
	{
		m_type = Type::VALUE;
		m_argument = argument;
		return *this;
	}

	std::string CommandOption::id() const
	{
		return m_id;
	}

	std::string CommandOption::longFlag() const
	{
		return m_longFlag;
	}

	std::string CommandOption::shortFlag() const
	{
		return m_shortFlag;
	}

	std::string CommandOption::description() const
	{
		return m_description;
	}

	bool CommandOption::hasLongFlag() const
	{
		return !m_longFlag.empty();
	}

	bool CommandOption::hasShortFlag() const
	{
		return !m_shortFlag.empty();
	}

	CommandOption::Type CommandOption::type() const
	{
		return m_type;
	}

	std::set<std::string> CommandOption::conflicts() const
	{
		return m_conflicts;
	}
}
