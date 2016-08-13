#pragma once

#include "Defines.h"
#include "Types.h"
#include "HandlePool.h"

#include <unordered_map>

EL_NAMESPACE()

class JsonString
{
private:
    int m_strHandle;
    size_t m_itemCount;

private:
    HandlePool<str_t>* m_pool;

public:
    JsonString(size_t capacity);
    virtual ~JsonString();

public:
    JsonString& BeginDict();
    JsonString& EndDict();

    JsonString& AddItem(const char* key, int value);

public:
    operator const char*();

private:
    void AddChar(char ch);
    void AddText(const char* text);
    void AddInt(int num);
    void AddComma();

private:
    HandlePool<str_t>& GetPool();

    str_t& GetString();
};

EL_NAMESPACE_END()
