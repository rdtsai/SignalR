#include <ctime>
#include <http_client.h>
#include "Connection.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

using namespace utility;
using namespace std;
using namespace web::json;

static void RunStreamingSample()
{
    //_CrtMemState s1, s2, s3;
    //_CrtMemCheckpoint(&s1);

    wcout << U("Choose transport:") << endl;
    wcout << U("1. AutoTransport") << endl;
    wcout << U("2. ServerSentEventsTransport") << endl;
    wcout << U("Option: ");

    string_t key;
    getline(wcin, key);

    if (key == U("1") || key == U("2"))
    {
        key.~basic_string(); // Memory leak detector complains that key is lost

        shared_ptr<Connection> connection = shared_ptr<Connection>(new Connection(U("http://localhost:40476/raw-connection")));
    
        connection->Received = [](string_t message)
        {
            wcout << message << endl;
        };

        connection->Reconnected = []()
        {
            time_t now = time(0);
            struct tm* nowStruct = localtime(&now);

            wcout << "[" << (nowStruct->tm_mon + 1) << "-" << nowStruct->tm_mday << "-" << (nowStruct->tm_year + 1900) << " "
                << nowStruct->tm_hour << ":" << nowStruct->tm_min << ":" << nowStruct->tm_sec << "]: Connection restablished" << endl;
        };

        connection->StateChanged = [](shared_ptr<StateChange> stateChange)
        {
            wcout << stateChange->GetOldStateName() << " => " << stateChange->GetNewStateName() << endl;
        };

        connection->Error = [](exception& ex)
        {
            wcerr << U("========ERROR==========") << endl;
            wcerr << ex.what() << endl;
            wcerr << U("=======================") << endl;
        };


        try
        {
            connection->Start().wait();

            wcout << U("Using ") << connection->GetTransport()->GetTransportName() << endl;
        }
        catch (exception& ex)
        {
            wcerr << U("========ERROR==========") << endl;
            wcerr << ex.what() << endl;
            wcerr << U("=======================") << endl;

            connection->Stop();
            return;
        }

        string_t line;
        getline(wcin, line);

        while (!line.empty())
        {
            value::field_map object;
            object.push_back(make_pair(value(U("type")), value(1)));
            object.push_back(make_pair(value(U("value")), value(line)));

            connection->Send(object).wait();

            getline(wcin, line);
        }

        connection->Stop();
    }  
    //_CrtMemCheckpoint(&s2);
    //if (_CrtMemDifference(&s3, &s1, &s2))
    //{
    //    _CrtMemDumpStatistics(&s3);
    //}
}

class B;

class A
{
public:
    shared_ptr<B> pB;
    int variable;
    void someFunction()
    {
        variable = 1;
    };
};

class B
{
public:
    function<void()> callBack;
};

int main () 
{
    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint(&s1);

    //bool testing = true;
    //if (testing)
    //{
    //    shared_ptr<A> pA = shared_ptr<A>(new A());
    //    pA->pB = shared_ptr<B>(new B());

    //    long count = pA.use_count();
    //    bool unique = pA.unique();

    //    pA->pB->callBack = [pA]()
    //    {
    //        pA->someFunction();
    //        long count = pA.use_count();
    //        bool unique = pA.unique();
    //    };

    //    unique = pA.unique();
    //    count = pA.use_count();

    //    pA->pB->callBack();

    //    int result = pA->variable;

    //    pA->pB->callBack = [](){};

    //    unique = pA.unique();
    //    count = pA.use_count();
    //}

    RunStreamingSample();

    wcout << U("Press <Enter> to Exit ...") << endl;
    getwchar();

    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2))
    {
        _CrtMemDumpStatistics(&s3);
    }
    
    //_CrtDumpMemoryLeaks();
}