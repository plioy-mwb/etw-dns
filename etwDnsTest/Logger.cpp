#include        "Logger.h"
#include        <iostream>
#include        <cstdarg>
#include        <time.h>

using namespace std;
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
void
    ConsoleLoggerChannel::              log                                 (const char* fmt, ...) {
        va_list va;
        va_start(va, fmt);
        char buffer [4096];
        vsprintf_s(buffer,fmt,va);
        cout << buffer << endl;
        va_end(va);
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    FileLoggerChannel::                 FileLoggerChannel                   (const char* logf) {
        _LogFile.open(logf, ofstream::out | ofstream::app);
        if (!_LogFile.is_open()) {
            printf("Can't open log file: %s",logf);
        }
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    FileLoggerChannel::                ~FileLoggerChannel                   () {
        _LogFile.flush();
        _LogFile.close();
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
void 
    FileLoggerChannel::                log                                  (const char* str,...) {
        // TODO handle var args
        _LogFile << str << std::endl;
        _LogFile.flush();
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    Logger::                           ~Logger                              () {
        for (auto channel : _LoggerChannels) {
           delete channel;
        }
        _LoggerChannels.clear();
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
void
    Logger::                            setLogLevel                         (LogLevel l) {
        _LogLevel = l;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
void
    Logger::                            addLoggerChannel                    (LoggerChannel* channel) {
        _LoggerChannels.push_back(channel);
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
void
    Logger::                            log                                 (LogLevel level, const char* fmt, ...) {
        if (level >= _LogLevel) {
            static const char* level_str[] = { "DEBUG", "INFO", "ERROR", "AUDIT" };
            va_list arg;
            va_start(arg, fmt);
            char str[1024];
            vsprintf_s(str, sizeof(str), fmt, arg);
            va_end(arg);

            time_t     now = time(0);
            struct tm  tstruct;
            char       tstr[80];
            localtime_s(&tstruct, &now);
            strftime(tstr, sizeof(tstr), "%Y-%m-%d.%X", &tstruct);

            char logstr[1250];
            sprintf_s(logstr, sizeof(logstr), "[%s][%s] - %s", level_str[level], tstr, str);
            for (auto& channel : _LoggerChannels) {
                channel->log(logstr);
            }
        }
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
