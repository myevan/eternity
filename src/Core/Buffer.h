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

    void Reset()
    {
        m_size = 0;
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

    bool Assign(size_t size, const byte_t* bytes)
    {
        if (m_capacity < size)
            return false;

        memcpy(m_bytes, bytes, size);
        m_size = size;
        return true;
    }

    bool Append(size_t size, const byte_t* bytes)
    {
        if (m_capacity < m_size + size)
            return false;

        memcpy(m_bytes + m_size, bytes, size);
        m_size += size;
        return true;
    }

    bool Append(size_t size, const char* chars)
    {
        if (m_capacity < m_size + size + 1)
            return false;

        memcpy(m_bytes + m_size, chars, size);
        m_size += size;

        m_bytes[m_size] = '\0';
        return true;
    }

    bool AddSize(size_t size)
    {
        if (m_capacity < m_size + size)
            return false;

        m_size += size;
        return true;
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
