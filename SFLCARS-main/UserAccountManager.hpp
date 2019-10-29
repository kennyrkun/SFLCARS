#ifndef USER_ACCOUNT_MANAGER_HPP
#define USER_ACCOUNT_MANAGER_HPP

class UserAccount;

#include <string>

class UserAccountManager
{
public:
	UserAccount* createUser(const std::string& username, const std::string& password);
	bool deleteUser(const std::string& username);

	bool doesUserExist(const std::string& username) const;

private:
	// TODO: move this somewhere it can be accessed by other people
	const std::string usersDirectory = "./sflcars/users/";
};

#endif // !USER_ACCOUNT_MANAGER_HPP