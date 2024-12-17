#include "CommandArgument.h"

namespace utils
{
	CommandArgument::CommandArgument(const std::string& id)
		: m_id(id), m_isRequired(false), m_isMultiple(false)
	{
	}

	CommandArgument& CommandArgument::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}

	CommandArgument& CommandArgument::setRequired(bool value)
	{
		m_isRequired = value;
		return *this;
	}

	CommandArgument& CommandArgument::setMultiple(bool value)
	{
		m_isMultiple = value;
		return *this;
	}

	std::string CommandArgument::id() const
	{
		return m_id;
	}

	std::string CommandArgument::description() const
	{
		return m_description;
	}

	bool CommandArgument::required() const
	{
		return m_isRequired;
	}

	bool CommandArgument::multiple() const
	{
		return m_isMultiple;
	}
}