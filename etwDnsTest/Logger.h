#pragma         once
#include        <vector>
#include        <fstream>
    
using namespace std;

//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    typedef enum {
                    DBG,
                    INF,
                    ERR,
                    ADT,
                    ALL = 255
    } 
    LogLevel;
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               LoggerChannel                       {
        public:
                    virtual            ~LoggerChannel() = default;
        protected:
                    virtual void        log(const char* str,...) = 0;
        
        friend class                    Logger;
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               FileLoggerChannel                   : public LoggerChannel {
        private:
                    ofstream            _LogFile;
        public:
                                        FileLoggerChannel(const char* logfile);
                    virtual            ~FileLoggerChannel();
        protected:
                    virtual void        log(const char* str,...);
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               ConsoleLoggerChannel                : public LoggerChannel {
        public:
                    virtual ~ConsoleLoggerChannel() = default;
        protected:
                    virtual void        log(const char* str,...);
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               Logger                              {
        private:
                    LogLevel            _LogLevel;
                    vector<LoggerChannel*> 
                                        _LoggerChannels;
        public:
                    virtual            ~Logger();
                    void                setLogLevel(LogLevel level);
                    void                addLoggerChannel(LoggerChannel* logger);
                    void                log(LogLevel level, const char* fmt, ...);
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------

