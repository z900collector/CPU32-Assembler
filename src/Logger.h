/**
 * Logger Class - A general logging class.
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */


#ifndef LOGGER_Header
#define LOGGER_Header

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


using namespace std;

class Logger
{
private:
static Logger* instance;
std::ofstream _log_file;
std::string   _log_dir;
std::string   _log_filename;
std::string   _logfile;

protected:
void setLogDir();
std::string getDateTime();
std::string getDate();

public:
void setFileName(std::string);
void setLogDir(std::string);
static Logger* getInstance();
void Start();
void LogFunction(std::string);
void LogMsg(std::string);
void LogMsg(std::stringstream);
void End();
};
#endif
