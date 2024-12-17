#ifndef UTILS_CMD_COMMAND_ARGUMENT_H
#define UTILS_CMD_COMMAND_ARGUMENT_H

#include <string>

namespace utils
{

	class CommandArgument
	{
	public:
		CommandArgument(const std::string& id);
		~CommandArgument() = default;

		CommandArgument& setDescription(const std::string& description);
		CommandArgument& setRequired(bool value);
		CommandArgument& setMultiple(bool value);

		std::string id() const;
		std::string description() const;
		bool required() const;
		bool multiple() const;

	private:
		std::string m_id;
		std::string m_description;
		bool m_isRequired;
		bool m_isMultiple;
	};
}

#endif // !UTILS_CMD_COMMAND_ARGUMENT_H
