#include <stdio.h>
#include <string.h>

#include <Core/Defines.h>
#include <Core/JsonWriter.h>
#include <Core/EventTarget.h>

int main()
{
    const char* a = "a";
    const char* b = "b";
    int x = 12345678;
    puts(EL_JSON(a, b, x));

    EL::EventTarget<int> OnNum;
    OnNum.Bind([](int num) { 
        puts(EL_JSON(num));
    });
    OnNum.Broadcast(99);
    return 0;
}
