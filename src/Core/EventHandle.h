#pragma once

#include "Defines.h"

EL_NAMESPACE()

typedef size_t EventHandle;

inline EventHandle AllocEventHandle()
{
        static size_t lastHandle = 1;
        size_t retHandle = lastHandle;
        lastHandle += 2;
        return retHandle;
}

EL_NAMESPACE_END()
