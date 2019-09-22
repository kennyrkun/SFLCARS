#include "Password.hpp"
#include "SettingsParser.hpp"
#include "PicoSHA256.hpp"

#include <string>
#include <ctime>

namespace sflcars
{
namespace utility
{

namespace password
{
	SaltedPassword hashPasswordWithSalt(const std::string& password, const std::string& salt)
	{
		std::string hash_hex_str = picosha2::hash256_hex_string(password + salt);

		return { hash_hex_str, salt };
	}

	std::string hashString(const std::string& string)
	{
		return picosha2::hash256_hex_string(string);
	}

	bool validatePassword(const std::string& password1, const std::string& password2)
	{
		return (password1 == password2);
	}
}

}
}
