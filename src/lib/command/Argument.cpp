#include "./Argument.h"

namespace cmd
{
	Argument::Argument(const std::string& id)
		: m_id(id), m_isRequired(false), m_isMultiple(false)
	{
	}

	Argument& Argument::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}

	Argument& Argument::setRequired(bool value)
	{
		m_isRequired = value;
		return *this;
	}

	Argument& Argument::setMultiple(bool value)
	{
		m_isMultiple = value;
		return *this;
	}

	std::string Argument::id() const
	{
		return m_id;
	}

	std::string Argument::description() const
	{
		return m_description;
	}

	bool Argument::required() const
	{
		return m_isRequired;
	}

	bool Argument::multiple() const
	{
		return m_isMultiple;
	}
}