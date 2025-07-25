#include "Option.hpp"

namespace cmd
{
	Option::Option(const std::string& id)
		: m_id(id), m_type(Option::Type::FLAG)
	{
	}
	
	Option& Option::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}
	
	Option& Option::setArgument(const std::string& defaultValue)
	{
		m_type = Type::ARGUMENT;
		m_defaultValue = defaultValue;
		m_argument = Argument(m_id).setRequired(true);
		return *this;
	}

	Option& Option::setMessage(const std::string& message)
	{
		m_type = Type::MESSAGE;
		m_message = message;
		return *this;
	}

	Option& Option::setShortFlag(char flag)
	{
		m_shortFlag = flag;
		return *this;
	}

	Option& Option::addConflict(const std::string& id)
	{
		m_conflictIds.insert(id);
		return *this;
	}

	Option::Type Option::type() const
	{
		return m_type;
	}

	std::string Option::id() const
	{
		return m_id;
	}

	std::string Option::description() const
	{
		return m_description;
	}

	std::string Option::defaultValue() const
	{
		return m_defaultValue;
	}

	std::string Option::message() const
	{
		return m_message;
	}

	char Option::shortFlag() const
	{
		return m_shortFlag.value();
	}

	bool Option::hasShortFlag() const
	{
		return m_shortFlag.has_value();
	}

	Argument Option::argument() const
	{
		return m_argument.value();
	}

	std::set<std::string> Option::conflicts() const
	{
		return m_conflictIds;
	}
}
