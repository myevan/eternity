#include "JsonString.h"

EL_NAMESPACE()

JsonString::JsonString(size_t capacity)
: m_itemCount(0)
{
    auto& pool = RefPool();
    m_buf = pool.Alloc();
    m_buf->Reserve(capacity);
}

JsonString::~JsonString()
{
    auto& pool = RefPool();
    pool.Free(m_buf);
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
    auto& buf = RefBuffer();
    return (const char*)buf.GetBytes();
}

void JsonString::AddChar(char ch)
{
    auto& buf = RefBuffer();
    buf.Append(1, &ch);
}

void JsonString::AddText(const char* text)
{
    size_t textSize = strlen(text);

    auto& buf = RefBuffer();
    buf.Append(1, "\"");
    buf.Append(textSize, text);
    buf.Append(1, "\"");
}

void JsonString::AddInt(int num)
{
    auto& buf = RefBuffer();

    char text[32];
    int textLen = snprintf(text, sizeof(text), "%d", num);
    if (0 < textLen)
    {
        buf.Append(textLen, text);
    }
    else
    {
        buf.Append(1, "?");
    }
}

void JsonString::AddComma()
{
    if (0 < m_itemCount)
    {
        AddChar(',');
    }
}

SharedPool<Buffer>& JsonString::RefPool()
{
    static SharedPool<Buffer> s_pool;
    return s_pool;
}

Buffer& JsonString::RefBuffer()
{
    return *m_buf;
}

EL_NAMESPACE_END()
