/**
 * Logger
 * A generic date/time stamped logging class for debug and monitoring.
 * This class is a singleton and once defined, we keep track of the returned
 * object pointer to access the basic log functions.
 *
 * Create a log-YYYY-MM-DD.log file in the current directory.
 * The log file can have a name of your choosing if you re-use this code elsewhere.
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */


#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <chrono>
#include <initializer_list>


#include "Logger.h"



using namespace std;


Logger* Logger::instance = 0;


Logger* Logger::getInstance()
{
        if(instance == 0)
        {
                instance = new Logger();
        }
        return instance;
}


std::string Logger::getDate()
{
        using namespace std::chrono;

        system_clock::time_point now = system_clock::now();
        time_t tt = system_clock::to_time_t(now);
        tm local_tm = *localtime(&tt);
        std::stringstream ss;
        std::stringstream day;
        std::stringstream month;
        month << setw(2)<< std::setfill('0')<<local_tm.tm_mon;
        day<< setw(2)<< std::setfill('0')<<local_tm.tm_mday;
        ss<<local_tm.tm_year+1900<<"-"<<month.str()<<"-"<<day.str();
        return ss.str();
}



std::string Logger::getDateTime()
{
        using namespace std::chrono;

        system_clock::time_point now = system_clock::now();
        time_t tt = system_clock::to_time_t(now);
        tm local_tm = *localtime(&tt);
        std::stringstream ss;
        std::stringstream day;
        std::stringstream month;
        month << setw(2)<< std::setfill('0')<<local_tm.tm_mon;
        day<< setw(2)<< std::setfill('0')<<local_tm.tm_mday;

        ss<<local_tm.tm_year+1900<<"-"<<month.str()<<"-"<<day.str()<<"|"<<local_tm.tm_hour<<":"<<local_tm.tm_min<<":"<<local_tm.tm_sec<<"|";
        return ss.str();
}



void Logger::setLogDir()
{
                  this->_logfile = this->_log_dir+"/"+this->_log_filename+"-"+this->getDate()+".log";
}



/**
 * Public Method - set the log dir to something like "/logs"
 */
void Logger::setLogDir(std::string ld)
{
        this->_log_dir = ld;
        this->setLogDir();
}



/**
 * Public Method - set the log filename
 */
void Logger::setFileName(std::string fn)
{
        this->_log_filename = fn;
        this->setLogDir();
}



void Logger::Start()
{
        this->setLogDir();
        _log_file.open(this->_logfile,std::ios_base::app);

        std::string time_string = this->getDateTime();
        _log_file<<time_string<<"S|============================================="<<std::endl;
        _log_file<<time_string<<"START"<<std::endl;
}



void Logger::LogFunction(std::string fs)
{
        std::string time_string = this->getDateTime();
        _log_file<<time_string<<"FUNC|"<<fs<<std::endl;
}


void Logger::LogMsg(std::stringstream ss)
{
        this->LogMsg( ss.str() );
}

void Logger::LogMsg(std::string s)
{
        std::string time_string = this->getDateTime();
        _log_file<<time_string<<"OK|"<<s<<std::endl;
}



void Logger::End()
{
        std::string time_string = this->getDateTime();
        _log_file<<time_string<<"END"<<std::endl;
        _log_file<<time_string<<"E|============================================="<<std::endl;
        _log_file.close();
}


/* End of file */
