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
		
		CommandArgument& setRequired(bool value);
		CommandArgument& setMany(bool value);

		std::string id() const;
		bool required() const;
		bool many() const;

	private:
		std::string m_id;
		bool m_required;
		bool m_many;
	};
}

#endif // !UTILS_CMD_COMMAND_ARGUMENT_H
