#pragma once

#include "Defines.h"
#include "Types.h"
#include "HandlePool.h"

#include <unordered_map>

#define _EL_JSON_STR_JOIN_1(_1) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).EndDict()

#define _EL_JSON_STR_JOIN_2(_1, _2) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).EndDict()

#define _EL_JSON_STR_JOIN_3(_1, _2, _3) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).EndDict()

#define _EL_JSON_STR_JOIN_4(_1, _2, _3, _4) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).AddItem(#_4, _4).EndDict()

#define _EL_JSON_STR_JOIN_5(_1, _2, _3, _4, _5) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).AddItem(#_4, _4).AddItem(#_5, _5).EndDict()

#define _EL_JSON_STR_JOIN_6(_1, _2, _3, _4, _5, _6) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).AddItem(#_4, _4).AddItem(#_5, _5).AddItem(#_6, _6).EndDict()

#define _EL_JSON_STR_SELECT(_6, _5, _4, _3, _2, _1, NAME, ...) NAME

#define EL_JSON_STR(...) _EL_JSON_STR_SELECT(__VA_ARGS__, \
    _EL_JSON_STR_JOIN_6, \
    _EL_JSON_STR_JOIN_5, _EL_JSON_STR_JOIN_4, _EL_JSON_STR_JOIN_3, _EL_JSON_STR_JOIN_2, _EL_JSON_STR_JOIN_1)(__VA_ARGS__)

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
