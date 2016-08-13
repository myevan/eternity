#pragma once

#include <assert.h>

#define EL_NAMESPACE()          namespace EL {
#define EL_NAMESPACE_END()      }

#define _EL_JSON_JOIN_1(_1) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).EndDict()

#define _EL_JSON_JOIN_2(_1, _2) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).EndDict()

#define _EL_JSON_JOIN_3(_1, _2, _3) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).EndDict()

#define _EL_JSON_JOIN_4(_1, _2, _3, _4) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).AddItem(#_4, _4).EndDict()

#define _EL_JSON_JOIN_5(_1, _2, _3, _4, _5) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).AddItem(#_4, _4).AddItem(#_5, _5).EndDict()

#define _EL_JSON_JOIN_6(_1, _2, _3, _4, _5, _6) \
    EL::JsonString(256).BeginDict().AddItem(#_1, _1).AddItem(#_2, _2).AddItem(#_3, _3).AddItem(#_4, _4).AddItem(#_5, _5).AddItem(#_6, _6).EndDict()

#define _EL_JSON_SELECT(_6, _5, _4, _3, _2, _1, NAME, ...) NAME

#define EL_JSON(...) _EL_JSON_SELECT(__VA_ARGS__, \
    _EL_JSON_JOIN_6, \
    _EL_JSON_JOIN_5, _EL_JSON_JOIN_4, _EL_JSON_JOIN_3, _EL_JSON_JOIN_2, _EL_JSON_JOIN_1)(__VA_ARGS__)


#define EL_VERIFY_V(cond, ...) {if (!(cond)) {assert(cond);return;}}
#define EL_VERIFY_U(cond, ...) {if (!(cond)) {assert(cond);return -1;}}
#define EL_VERIFY_P(cond, ...) {if (!(cond)) {assert(cond);return nullptr;}}
