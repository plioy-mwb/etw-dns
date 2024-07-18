#define INITGUID                        //Turns the DEFINE_GUID for EventTraceGuid into a const.          

#include        <signal.h>
#include        "DnsSensor.h"
#include        "ProviderHandler.h"
#include        "Logger.h"

#include        <conio.h>

bool            running     =   true;
Logger          dbg;
//DnsSensor       sensor;

//{ 0x1C95126E, 0x7EEA, 0x49A9, { 0xA3, 0xFE, 0xA3, 0x78, 0xB0, 0x3D, 0xDB, 0x4D } }
ProviderHandler sensor((LPWSTR)L"Fake Provider Name", { 0xA0C1853B, 0x5C40, 0x4B15, { 0x87, 0x66, 0x3C, 0xF1, 0xC5, 0x8F, 0x98, 0x5A }});
HANDLE          hEvent;

//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    void                                SignalHandler                       (int signal) {
        dbg.log(INF, "Signal received. Terminating process");
        sensor.stop();
        running = FALSE;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    typedef void                        (*SignalHandlerPointer)             (int);
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    BOOL                                CtrlHandler                         (DWORD fdwCtrlType) {
        SetEvent(hEvent);
        SignalHandler(fdwCtrlType);
        switch (fdwCtrlType) {
            case CTRL_C_EVENT:
                printf("Ctrl-C event\n\n");
            break;  

            case CTRL_CLOSE_EVENT:
                printf("Ctrl-Close event\n\n");
            break;

            case CTRL_BREAK_EVENT:
                printf("Ctrl-Break event\n\n");
            break;

            case CTRL_LOGOFF_EVENT:
                printf("Ctrl-Logoff event\n\n");
            break;

            case CTRL_SHUTDOWN_EVENT:
                printf("Ctrl-Shutdown event\n\n");
            break;

            default:
            break;
        }
        return TRUE;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    int									readKey                             () {
        printf("\nplease press any key ..\n");
        return _getch();
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    int                                 wmain                               (void) {
        hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true))  {    }
        else printf("\nERROR: Could not set control handler");

        dbg.addLoggerChannel(new ConsoleLoggerChannel());
        dbg.addLoggerChannel(new FileLoggerChannel("app.log"));
        dbg.setLogLevel(DBG);

        dbg.log(INF, "Starting Application");

        Logger auditLog;
        auditLog.setLogLevel(ALL);
        auditLog.addLoggerChannel(new FileLoggerChannel("audit.log"));

        sensor.setAuditLogger(&auditLog);
        sensor.setSystemLogger(&dbg);

        bool started = sensor.start();

        if(started) {
            SignalHandlerPointer previousHandler;
            previousHandler = signal(SIGINT     , SignalHandler);
            previousHandler = signal(SIGILL     , SignalHandler);
            previousHandler = signal(SIGTERM    , SignalHandler);
            previousHandler = signal(SIGABRT    , SignalHandler);
            previousHandler = signal(SIGSEGV    , SignalHandler);
            previousHandler = signal(SIGBREAK   , SignalHandler);


            time_t lastUpdate = time(NULL);
            int printInfoFreq = 5;
            while (running) {
                if ((time(NULL) - lastUpdate) > printInfoFreq)  {
                    wprintf(L"%s", sensor.getInfo().data());
                    lastUpdate = time(NULL);
                }
                Sleep(10);
            }
            sensor.stop();
            wprintf(L"%s", sensor.getInfo().data());
        }

        dbg.log(INF, "etw-dns Application stopped");

        readKey();
        if (hEvent) CloseHandle(hEvent);
        return 0;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------

