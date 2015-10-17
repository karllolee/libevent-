/*
 * Logger.h
 *
 *  Created on: 2015Äê10ÔÂ17ÈÕ
 *      Author: wenge
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
namespace libevent_cpp{

class Logger{
public:

	Logger(char* fileName = NULL){
		if (fileName != NULL){
			file_ = ::fopen(fileName, "w");
			if (file_ == NULL){
				::perror("log open fail");
				::abort();
			}
		}else{
			file_ = stdout;
		}
	}

	~Logger(){
		if (file_ != stdout)
			::fclose(file_);
	}

	void LOG_FATAL(const char* fmt, ...){
		va_list ap;
		va_start(ap, fmt);
		log_internal("FATAL", fmt, ap);
		va_end(ap);
		::abort();
	}

	void LOG_ERROR(const char* fmt, ...){
		va_list ap;
		va_start(ap, fmt);
		log_internal("ERROR", fmt, ap);
		va_end(ap);
		::abort();
	}

	void LOG_WARN(const char* fmt, ...){
		va_list ap;
		va_start(ap, fmt);
		log_internal("WARN", fmt, ap);
		va_end(ap);
	}

	void LOG_INFO(const char* fmt, ...){
		va_list ap;
		va_start(ap, fmt);
		log_internal("INFO", fmt, ap);
		va_end(ap);
	}

	void LOG_DEBUG(const char* fmt, ...){
		va_list ap;
		va_start(ap, fmt);
		log_internal("DEBUG", fmt, ap);
		va_end(ap);
	}
private:
	Logger(const Logger&);
	Logger& operator=(const Logger&);

	void log_internal(const char* level, const char* fmt, va_list ap){
	    size_t len = ::strlen(level);
	    if (len > 4096){
	    	::perror("log message too long");
	    	len = 4096;
	    }
	    ::memset(buffer_, 0, sizeof(buffer_));
	    ::memcpy(buffer_, level, len);
	    buffer_[len] = ':';
	    ::vsnprintf (buffer_ + len + 1, sizeof(buffer_), fmt, ap);
	    log_to_file();
	}

	void log_to_file(){
		if (::fwrite(buffer_, sizeof(char), ::strlen(buffer_), file_) < 0)
			::perror("log to file fail");
	}

	FILE* file_;
	char buffer_[4102];
};

class LoggerSingleton{
public:
	static Logger* getLogger(){
		static Logger logger;
		return &logger;
	}
private:
	LoggerSingleton(const LoggerSingleton&);
	LoggerSingleton& operator=(const LoggerSingleton&);
};

}


#endif /* LOGGER_H_ */
