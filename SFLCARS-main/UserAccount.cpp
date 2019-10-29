#include "UserAccount.hpp"

UserAccount::UserAccount(const std::string& username) : username(username)
{
}

std::string UserAccount::getUsername() const
{
	return username;
}

bool UserAccount::setUsername(const std::string& newUsername)
{
	return false;
}
