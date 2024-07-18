#include        "ProviderHandler.h"
#include        <set>
#include        <algorithm>
#include        <functional>
#include        <psapi.h>
#include        <locale>
#include        <codecvt>
#include        <sstream>

#pragma comment(lib, "psapi.lib")
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    ProviderHandler::                   ProviderHandler(LPWSTR providerName, const GUID providerGUID)
                                        : WinETWSensor(providerName, providerGUID) {
        _Stats.TotalEvents              = 0;
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    void       
    ProviderHandler::                   eventReceived                       (PEVENT_RECORD evt) {
        EVENT_DESCRIPTOR* evDesc = &evt->EventHeader.EventDescriptor;
        //void*     evData = evt->UserData;
        PBYTE value = NULL;
        bool res=getPropertyValue(evt,(LPWSTR)L"ContextInfo",&value);
        if (res) {
            wstring wstr;
            _logger->log(DBG,"value: %S",(LPWSTR)value);
        }
        _logger->log(DBG, ">> eventReceived: %d : %ul",evDesc->Id, evDesc->Keyword);
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    wstring
    ProviderHandler::                   getInfo                             () {
        return L"no info";
    }
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
