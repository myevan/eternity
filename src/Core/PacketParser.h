#pragma once

EL_NAMESPACE()

class PacketParser
{
public:
    virtual ~PacketParser()
    {}

public:
    virtual size_t Parse(size_t size, const byte_t* bytes, PacketQueue& outPacketQueue) = 0;

};


EL_NAMESPACE_END()
