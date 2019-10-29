#include "UserAccountManager.hpp"

#include "UserAccount.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

UserAccount* UserAccountManager::createUser(const std::string& username, const std::string& password)
{
	if (doesUserExist(username))
	{
		std::cerr << "user already exists" << std::endl;
		return nullptr;
	}

	try
	{
		fs::create_directories(usersDirectory + username);

		std::ofstream createFile(usersDirectory + username, std::ios::out | std::ios::binary);

		if (!createFile.is_open())
		{
			std::cerr << "failed to create user file" << std::endl;
			return nullptr;
		}

		createFile.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "failed to create user" << std::endl;
		return nullptr;
	}

	return new UserAccount(username);
}

bool UserAccountManager::deleteUser(const std::string& username)
{
	if (doesUserExist(username))
	{
		std::cerr << "user does not exist" << std::endl;
		return false;
	}

	try
	{
		fs::remove_all(usersDirectory + username);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "failed to delete user." << std::endl;
		return false;
	}

	return true;
}

bool UserAccountManager::doesUserExist(const std::string& username) const
{
	if (fs::exists(usersDirectory + username))
		return true;
	else
		return false;
}
