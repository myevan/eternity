#pragma once

#include "Defines.h"
#include "Types.h"

#define EL_TYPE_FOURCC_DECLARE(T, v)    template<> struct EL::TypeFourCC<T> { enum { Num = v }; };

EL_NAMESPACE()

template<typename T>
struct TypeFourCC
{
	enum
	{
		Num = 0
	};
};

EL_NAMESPACE_END()

EL_TYPE_FOURCC_DECLARE(int, EL_STRING_FOURCC_NUM("___i"))
EL_TYPE_FOURCC_DECLARE(float, EL_STRING_FOURCC_NUM("___f"))
EL_TYPE_FOURCC_DECLARE(std::string, EL_STRING_FOURCC_NUM("__ss"))
