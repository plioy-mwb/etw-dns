#pragma         once
#include        "WinETWSensor.h"
#include        <map>
#include        <mutex>

using namespace std;

//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    typedef 
    map<wstring, UINT64>                WStringCounterMap;
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    struct                              DnsStats                            {
        WStringCounterMap               DomainCounter;
        WStringCounterMap               ProcessCounter;
        UINT64                          TotalQueries;
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
    class                               DnsSensor                           : public WinETWSensor {
        public:
                                        DnsSensor                           ();
                    virtual            ~DnsSensor                           () = default;
                    virtual wstring     getInfo                             ();
        private:
                    DnsStats            _Stats;
                    mutex               _Lock;
        protected:
                    void                eventReceived                       (PEVENT_RECORD evt) override;
    };
//  ----------------------------------- ----------------------------------- ----------------------------------------------------------------
