#pragma once

#include "Types.h"
#include "TypeFourCC.h"

#include <vector>

EL_NAMESPACE()

class Payload
{
private:
	fcc_t m_fcc;
	std::vector<byte_t> m_bytes;

public:
	bool SetBytes(fcc_t fcc, size_t size, const byte_t* bytes);
	bool SetString(const char_t* inValue);
	bool SetString(str_t& inValue);

public:
	const byte_t* PeekBytes(fcc_t fcc, size_t size) const;
	const char_t* PeekString();

public:
	fcc_t GetFourCC();
	str_t GetString();

public:
	template<typename T>
	bool Set(const T& inValue)
	{
		fcc_t fcc = { TypeFourCC<T>::Num };
		assert(fcc.num != 0 && "CHECKME:TypeFourCC");
		return SetBytes(fcc, sizeof(T), (const byte_t*)&inValue);
	}

	template<typename T>
	bool Get(T& outValue)
	{
		auto* ptrValue = Peek<T>();
		if (ptrValue == nullptr)
			return false;
		
		outValue = *ptrValue;
		return true;
	}

	template<typename T>
	const T& Get()
	{
		auto* ptrValue = Peek<T>();
		if (ptrValue == nullptr)
		{
			static T defValue;
			return defValue;
		}
		return *ptrValue;
	}

	template<typename T>
	const T* Peek() const
	{
		fcc_t fcc = { TypeFourCC<T>::Num };
		assert(fcc.num != 0 && "CHECKME:TypeFourCC");
		return reinterpret_cast<const T*>(PeekBytes(fcc, sizeof(T)));
	}

	template<typename T>
	const T* Peek(size_t size) const
	{
		fcc_t fcc = { TypeFourCC<T>::Num };
		assert(fcc.num != 0 && "CHECKME:TypeFourCC");
		return reinterpret_cast<const T*>(PeekBytes(fcc, size));
	}
};

EL_NAMESPACE_END()
