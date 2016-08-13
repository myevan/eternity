#include <stdio.h>
#include <string.h>

#include <Core/Defines.h>
#include <Core/Types.h>
#include <Core/JsonWriter.h>
#include <Core/EventTarget.h>

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
    return 0;
}
