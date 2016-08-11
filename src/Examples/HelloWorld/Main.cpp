#include <stdio.h>
#include <string.h>

#include <Core/Defines.h>
#include <Core/JsonWriter.h>

int main()
{
    const char* a = "a";
    const char* b = "b";
    int x = 12345678;
    puts(EL_JSON(a, b, x));
    return 0;
}
