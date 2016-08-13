#include <stdio.h>
#include <string.h>

#include <Core/Defines.h>
#include <Core/Types.h>
#include <Core/JsonWriter.h>
#include <Core/EventTarget.h>
#include <Core/HandlePool.h>
#include <Core/Payload.h>

int main()
{
    using namespace EL;

    const char_t* a = "a";
    const char_t* b = "b";
    int_t x = 12345678;
    puts(EL_JSON(a, b, x));

    EventTarget<int> OnNum;
    OnNum.Bind([](int num) { 
        puts(EL_JSON(num));
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
