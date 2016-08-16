#include <stdio.h>

#include <Core/Defines.h>
#include <Core/Types.h>
#include <Core/JsonString.h>
#include <Core/EventTarget.h>
#include <Core/HandlePool.h>
#include <Core/Payload.h>

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

    return 0;
}
