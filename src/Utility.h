/**
 * Utility Header file
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef Utility_Class_Header
#define Utility_Class_Header

#include <string>
#include <vector>

class Utility
{
public:
unsigned int getRegisterMask(char, unsigned int);
unsigned int getRegister(std::string);
std::string ltrim(std::string str);
std::string rtrim(std::string str);
std::vector<std::string> split(const std::string& );
};
#endif
