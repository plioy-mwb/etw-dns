#include        "AgentSensor.h"
#include        <thread>
#include        <locale>
#include        <codecvt>

//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    AgentSensor::                       AgentSensor                         () {
        _logger         = NULL;
        _AuditLogger    = NULL;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    void
    AgentSensor::                       setSystemLogger                     (Logger* logger) {
        _logger = logger;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    void
    AgentSensor::                       setAuditLogger                      (Logger* logger) {
        _AuditLogger = logger;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    Logger*
    AgentSensor::                       getSystemLogger                     () {
        return _logger;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    Logger*
    AgentSensor::                       getAuditLogger                      () {
        return _AuditLogger;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    bool
    AgentSensor::                       start                               () {
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        std::string n = converter.to_bytes(_Name);

        _logger->log(INF, "Starting %s sensor", n.c_str());
        if (!init()) {
            _logger->log(ERR, "Sensor initialization failed. Aborting start.");
            return false;
        }
        _ThreadId = std::thread(&AgentSensor::runSensor, this);
        _logger->log(INF, "Sensor %s started.", n.c_str());
        return true;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    void
    AgentSensor::                       stop                                () {
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        std::string n = converter.to_bytes(_Name);

        _logger->log(INF, "Stopping %s sensor", n.c_str());
        stopSensor();
        try {
            _ThreadId.join();
        }
        catch (std::exception e) {
            _logger->log(ERR,"Error Joining Thread: %s",e.what());
        }
        _logger->log(INF, "Sensor %s stopped", n.c_str());
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    bool
    AgentSensor::                       isRunning                           () {
        return false;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
