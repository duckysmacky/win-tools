#include "CommandArgument.h"

namespace utils
{
	CommandArgument::CommandArgument(const std::string& id)
		: m_id(id), m_required(false), m_many(false)
	{
		
	}

	CommandArgument& CommandArgument::setRequired(bool value)
	{
		m_required = value;
		return *this;
	}

	CommandArgument& CommandArgument::setMany(bool value)
	{
		m_many = value;
		return *this;
	}

	std::string CommandArgument::id() const
	{
		return m_id;
	}

	bool CommandArgument::required() const
	{
		return m_required;
	}

	bool CommandArgument::many() const
	{
		return m_many;
	}
}