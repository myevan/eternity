#pragma once

#include <assert.h>

#define EL_NAMESPACE()          namespace EL {
#define EL_NAMESPACE_END()      }

#define EL_VERIFY_V(cond, ...) {if (!(cond)) {assert(cond);return;}}
#define EL_VERIFY_U(cond, ...) {if (!(cond)) {assert(cond);return -1;}}
#define EL_VERIFY_P(cond, ...) {if (!(cond)) {assert(cond);return nullptr;}}
