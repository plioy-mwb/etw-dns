#pragma         once
#include        "Logger.h"
#include        <string>
#include        <mutex>

using namespace         std;

//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               AgentSensor                         {
        protected:
                        wstring         _Name;
                        thread          _ThreadId;
                        Logger*         _logger;
                        Logger*         _AuditLogger;
        protected:
                        virtual bool    init() = 0;
                        virtual void    runSensor() = 0;
                        virtual void    stopSensor() = 0;
        public:
                                        AgentSensor();
                        virtual        ~AgentSensor() = default;
                        virtual bool    start();
                        virtual void    stop();
                        bool            isRunning();
                        void            setSystemLogger(Logger* logger);
                        void            setAuditLogger(Logger* logger);
                        Logger*         getSystemLogger();
                        Logger*         getAuditLogger();
                        virtual wstring getInfo() = 0;
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
