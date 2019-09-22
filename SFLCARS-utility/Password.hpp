#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>

namespace sflcars
{
namespace utility
{

namespace password
{
	struct SaltedPassword
	{
		std::string hash;
		std::string salt;
	};

	SaltedPassword hashPasswordWithSalt(const std::string& password, const std::string& salt);

	std::string hashString(const std::string& string);

    bool validatePassword(const std::string& username, const std::string& password);
}

}
}

#endif // !PASSWORD_HPP