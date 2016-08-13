#include "JsonString.h"

EL_NAMESPACE()

JsonString::JsonString(size_t capacity)
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

JsonString::~JsonString()
{
    auto& str = GetString();
    str = "";

    auto& pool = GetPool();
    pool.Free(m_strHandle);
}

JsonString& JsonString::BeginDict()
{
    AddChar('{');
    return *this;
}

JsonString& JsonString::EndDict()
{
    AddChar('}');
    m_itemCount = 0;
    return *this;
}

JsonString& JsonString::AddItem(const char* key, int value)
{
    AddComma();
    AddText(key);
    AddChar(':');
    AddInt(value);
    
    m_itemCount++;
    return *this;
}

JsonString::operator const char*()
{
    auto& str = GetString();
    return str.c_str();
}

void JsonString::AddChar(char ch)
{
    auto& str = GetString();
    str += ch;
}

void JsonString::AddText(const char* text)
{
    auto& str = GetString();
    str += '"';
    str.append(text);
    str += '"';
}

void JsonString::AddInt(int num)
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

void JsonString::AddComma()
{
    if (0 < m_itemCount)
    {
        AddChar(',');
    }
}

HandlePool<str_t>& JsonString::GetPool()
{
    assert(m_pool != nullptr);
    return *m_pool;
}

str_t& JsonString::GetString()
{
    auto& pool = GetPool();
    return pool.RefObject(m_strHandle);
}

EL_NAMESPACE_END()
