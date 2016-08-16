#pragma once

#include "PacketParser.h"

EL_NAMESPACE()

class TextPacketParser : public PacketParser
{
public:
    virtual size_t Parse(size_t size, const byte_t* bytes, PacketQueue& outPacketQueue) override
    {
        // outPacketQueue.Reset();

        size_t baseOffset = 0;
        size_t curOffset = 0;
        for (curOffset = 0; curOffset != size; ++curOffset)
        {
            switch (bytes[curOffset])
            {
                case '\r':
                    outPacketQueue.Push(curOffset - baseOffset, bytes + baseOffset);
                    if (curOffset + 1 < size && bytes[curOffset + 1] == '\n')
                        curOffset++;
                    break;
                case '\n':
                    outPacketQueue.Push(curOffset - baseOffset, bytes + baseOffset);
                    break;
                default:
                    break;
            }
        }

        return curOffset;
    }
};

EL_NAMESPACE_END()
