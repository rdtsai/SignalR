#pragma once

#include <string>
#include "Connection.h"

using namespace std;
using namespace utility;
using namespace web::json;

class TransportHelper
{
public:
    TransportHelper(void);
    ~TransportHelper(void);

    static pplx::task<NegotiationResponse*> GetNegotiationResponse(http_client* client, Connection* connnection);
    static string_t GetReceiveQueryString(Connection* connection, string_t data, string_t transport);
    static void ProcessMessages(Connection* connection, string raw, bool* timedOut, bool* disconnected);
    static void ProcessResponse(Connection* connection, string_t response, bool* timeOut, bool* disconnected, function<void()> onInitialized);
private:
    struct NegotiationRequestInfo
    {
        void* UserState;
        IClientTransport::NEGOTIATE_CALLBACK Callback;
    };

    static string_t CleanString(string_t uri);
    static string_t EncodeUri(string_t uri);
    static void UpdateGroups(Connection* connection, string_t groupsToken);
    static void TryInitialize(value response, function<void()> onInitialized);
};

