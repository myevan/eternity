#pragma once

#include "Types.h"

EL_NAMESPACE()

class Sequence32
{
public:
    static Sequence32& Get()
    {
        static Sequence32 s_instance;
        return s_instance;
    }

private:
    uint32_t m_num;

public:
    Sequence32()
    : m_num(1)
    {
    }

public:
    uint32_t Alloc()
    {
        uint32_t ret = m_num;
        m_num += 2; // NOTE: 1부터 시작해서 2씩 증가하면 오버플로우되더라도 0이 되지 않음
        return ret;
    }
};


EL_NAMESPACE_END()
