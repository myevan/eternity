#pragma once

#include "Defines.h"
#include "HandlePool.h"

#include <unordered_map>

EL_NAMESPACE()

class JsonString
{
private:
    int m_strHandle;
    size_t m_itemCount;

private:
    HandlePool<std::string>* m_pool;

public:
    JsonString(size_t capacity)
    : m_strHandle(0)
    , m_itemCount(0)
    {
        static std::unordered_map<size_t, HandlePool<std::string>> s_poolDict;
        m_pool = &s_poolDict[capacity];

        auto& pool = GetPool();
        m_strHandle = pool.Alloc();

        auto& str = GetString();
        str.reserve(capacity);
    }

    ~JsonString()
    {
        auto& str = GetString();
        str = "";

        auto& pool = GetPool();
        pool.Free(m_strHandle);
    }

    HandlePool<std::string>& GetPool()
    {
        assert(m_pool != nullptr);
        return *m_pool;
    }

    JsonString& BeginDict()
    {
        AddChar('{');
        return *this;
    }

    JsonString& EndDict()
    {
        AddChar('}');
        m_itemCount = 0;
        return *this;
    }

    JsonString& AddItem(const char* key, int value)
    {
        AddComma();
        AddText(key);
        AddChar(':');
        AddInt(value);
        
        m_itemCount++;
        return *this;
    }

public:
    operator const char*()
    {
        auto& str = GetString();
        return str.c_str();
    }

private:
    void AddChar(char ch)
    {
        auto& str = GetString();
        str += ch;
    }

    void AddText(const char* text)
    {
        auto& str = GetString();
        str += '"';
        str.append(text);
        str += '"';
    }

    void AddInt(int num)
    {
        auto& str = GetString();

        char buf[32];
        int numLen = snprintf(buf, sizeof(buf), "%d", num);
        if (0 < numLen)
        {
            str.append(buf, numLen);
        }
        else
        {
            str.append(buf, '0');
        }
    }

    void AddComma()
    {
        if (0 < m_itemCount)
        {
            AddChar(',');
        }
    }

private:
    std::string& GetString()
    {
        auto& pool = GetPool();
        return pool.RefObject(m_strHandle);
    }
};

EL_NAMESPACE_END()
