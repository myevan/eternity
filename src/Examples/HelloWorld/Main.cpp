#include <stdio.h>
#include <string.h>

#include <Core/Defines.h>
#include <Core/Types.h>
#include <Core/JsonString.h>
#include <Core/EventTarget.h>
#include <Core/HandlePool.h>
#include <Core/Payload.h>

#include <Boost/SocketServer.h>

#include <boost/asio.hpp>

int main()
{
    using namespace EL;

    puts(JsonString(32).BeginDict().AddItem("a", 1).AddItem("b", 2).EndDict());

    EventTarget<int> OnNum;
    OnNum.Bind([](int num) 
    {
        puts(EL_JSON_STR(num)); 
    });
    OnNum.Broadcast(99);

    HandlePool<Payload> payloadPool;
    int_t h = payloadPool.Alloc();
    auto& payload = payloadPool.RefObject(h);
    payload.SetString("Hello");
    puts(payload.GetString().c_str());
    payloadPool.Free(h);

    boost::asio::io_service service;

    auto server = std::make_shared<SocketServer>(service, 5000);
    server->Start();

    service.run();

    return 0;
}
