#pragma once

#include "Defines.h"
#include "Types.h"

EL_NAMESPACE()

class Buffer
{
private:
    size_t m_capacity;
    size_t m_size;
    byte_t* m_bytes;

public:
    Buffer()
    : m_capacity(0)
    , m_size(0)
    , m_bytes(nullptr)
    {
    }

    virtual ~Buffer()
    {
        if (m_bytes != nullptr)
        {
            free(m_bytes);
        }
    }

    void Reserve(size_t capacity)
    {
        if (capacity <= m_capacity)
            return;

        byte_t* oldBytes = m_bytes;
        byte_t* newBytes = (byte_t*)malloc(capacity);
        if (oldBytes != nullptr)
        {
            if (m_size != 0)
            {
                memcpy(newBytes, oldBytes, m_size);
            }
            free(oldBytes);
        }

        m_capacity = capacity;
        m_bytes = newBytes;
    }

    void Assign(size_t size, const byte_t* bytes)
    {
        assert(size < m_capacity);
        memcpy(m_bytes, bytes, size);
        m_size = size;
    }

    void AddSize(size_t size)
    {
        assert(m_size + size < m_capacity);
        m_size += size;
    }

    void RemoveHead(size_t size)
    {
        assert(size <= m_size);
        size_t remainingSize = m_size - size; 
        memmove(m_bytes, m_bytes + m_size, remainingSize);
        m_size = remainingSize;
    }

public:
    size_t GetSize()
    { return m_size; }

    size_t GetSlackSize()
    { return m_capacity - m_size; }

    byte_t* GetBytes()
    { return m_bytes; }

    byte_t* GetSlackBytes()
    { return m_bytes + m_size; }
};

EL_NAMESPACE_END()
