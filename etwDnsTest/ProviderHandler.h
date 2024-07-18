#pragma         once
#include        "WinETWSensor.h"
#include        <map>
#include        <mutex>
using namespace std;
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    typedef
    map<wstring, UINT64>                WStringCounterMap;
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    struct                              ProviderStats                       {
        UINT64                          TotalEvents;
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               ProviderHandler                     : public WinETWSensor {
        public:
                                        ProviderHandler                     (LPWSTR providerName, const GUID providerGUID);
                    virtual            ~ProviderHandler                     () = default;
                    virtual wstring     getInfo                             ();
        private:
                    ProviderStats       _Stats;
                    mutex               _Lock;
        protected:
                    void                eventReceived                       (PEVENT_RECORD evt) override;
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
