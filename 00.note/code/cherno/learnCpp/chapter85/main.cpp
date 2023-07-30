#include <iostream>
#include <string>

void PrintName(const std::string& name)
{
	std::cout << "[lvalue] " << name << std::endl;
}

void PrintName(std::string&& name)
{
	std::cout << "[rvalue] " << name << std::endl;
}

int main()
{
	std::string firstName = "Yan";
	std::string lastName = "Chernikov";

	std::string fullName = firstName + lastName;

	PrintName(firstName);
	PrintName(firstName + lastName);

	std::cin.get();
}