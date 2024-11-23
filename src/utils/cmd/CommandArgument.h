#ifndef UTILS_CMD_COMMAND_ARGUMENT_H
#define UTILS_CMD_COMMAND_ARGUMENT_H

#include <string>

namespace utils::cmd
{
	class CommandArgument
	{
	public:
		CommandArgument(const std::string& id);
		~CommandArgument() = default;
		
		void isRequired(bool value);
		void isMany(bool value);

		std::string id();
		bool required();
		bool many();

	private:
		std::string m_id;
		bool m_required;
		bool m_many;
	};
}

#endif // !UTILS_CMD_COMMAND_ARGUMENT_H
