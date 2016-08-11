#pragma once

#define _EL_JSON_JOIN_1(_1) \
    JsonWriter().Begin().Add(#_1, _1).End()

#define _EL_JSON_JOIN_2(_1, _2) \
    JsonWriter().Begin().Add(#_1, _1).Add(#_2, _2).End()

#define _EL_JSON_JOIN_3(_1, _2, _3) \
    JsonWriter().Begin().Add(#_1, _1).Add(#_2, _2).Add(#_3, _3).End()

#define _EL_JSON_JOIN_4(_1, _2, _3, _4) \
    JsonWriter().Begin().Add(#_1, _1).Add(#_2, _2).Add(#_3, _3).Add(#_4, _4).End()

#define _EL_JSON_JOIN_5(_1, _2, _3, _4, _5) \
    JsonWriter().Begin().Add(#_1, _1).Add(#_2, _2).Add(#_3, _3).Add(#_4, _4).Add(#_5, _5).End()

#define _EL_JSON_JOIN_6(_1, _2, _3, _4, _5, _6) \
    JsonWriter().Begin().Add(#_1, _1).Add(#_2, _2).Add(#_3, _3).Add(#_4, _4).Add(#_5, _5).Add(#_6, _6).End()

#define _EL_JSON_SELECT(_6, _5, _4, _3, _2, _1, NAME, ...) NAME

#define EL_JSON(...) _EL_JSON_SELECT(__VA_ARGS__, \
    _EL_JSON_JOIN_6, \
    _EL_JSON_JOIN_5, _EL_JSON_JOIN_4, _EL_JSON_JOIN_3, _EL_JSON_JOIN_2, _EL_JSON_JOIN_1)(__VA_ARGS__)

