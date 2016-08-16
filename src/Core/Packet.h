#pragma once

#include "Defines.h"
#include "Types.h"

EL_NAMESPACE()

class Packet
{
private:
    size_t m_size;
    const byte_t* m_bytes;

public:
    Packet()
    : m_size(0)
    , m_bytes(nullptr)
    {}

    void Assign(size_t size, const byte_t* bytes)
    {
        m_size = size;
        m_bytes = bytes;
    }

public:
    size_t GetSize() const
    { return m_size; }

    const byte_t* GetBytes() const
    { return m_bytes; }
};

EL_NAMESPACE_END()
