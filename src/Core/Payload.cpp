#include "Payload.h"

EL_NAMESPACE()

Payload::Payload()
: m_fcc({0})
{}

bool Payload::SetBytes(fcc_t fcc, size_t size, const byte_t* bytes)
{
	if (0 < size)
	{
		m_bytes.assign(bytes, bytes + size);
	}
	else
	{
		m_bytes.clear();
	}

	m_fcc = fcc;
	return true;
}

bool Payload::SetString(const char* inValue)
{
	fcc_t fcc = { TypeFourCC<std::string>::Num };
	assert(fcc.num != 0 && "CHECKME:TypeFourCC");
	return SetBytes(fcc, strlen(inValue) + 1, (const byte_t*)inValue);
}

bool Payload::SetString(std::string& inValue)
{
	fcc_t fcc = { TypeFourCC<std::string>::Num };
	assert(fcc.num != 0 && "CHECKME:TypeFourCC");
	return SetBytes(fcc, inValue.length() + 1, (const byte_t*)inValue.c_str());
}

const uint8_t* Payload::PeekBytes(fcc_t fcc, size_t size) const
{
	if (m_fcc.num != fcc.num)
		return nullptr;

	if (m_bytes.size() < size)
		return nullptr;

	return &m_bytes[0];
}

const char* Payload::PeekString()
{
	fcc_t fcc = { TypeFourCC<std::string>::Num };
	if (m_fcc.num != fcc.num)
		return nullptr;

	return (const char*)&m_bytes[0];
}

fcc_t Payload::GetFourCC()
{
	return m_fcc;
}

std::string Payload::GetString()
{
	if (0 < m_bytes.size())
	{
		const char* ptrChars = PeekString();
		return std::string(ptrChars, m_bytes.size() - 1);
	}
	else
	{
		static std::string defValue;
		return defValue;
	}
}

EL_NAMESPACE_END()
