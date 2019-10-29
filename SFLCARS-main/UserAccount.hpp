#ifndef USER_ACCOUNT_HPP
#define USER_ACCOUNT_HPP

#include <string>

class UserAccount
{
public:
	UserAccount(const std::string& username);

	std::string getUsername() const;
	bool setUsername(const std::string& newUsername);

	// TODO: these will be implemented when offline stuff is implemented
	// i.e. "remember me"
	// this will be set in user settings
	//bool setPassword(const std::string& newPassword);
	//bool validatePassword(const std::string& password);

private:
	std::string username;
};

#endif // !USER_ACCOUNT_HPP