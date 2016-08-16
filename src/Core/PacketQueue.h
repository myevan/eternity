#pragma once

#include "HandlePool.h"
#include "Packet.h"

EL_NAMESPACE()

class PacketQueue
{
private:
    HandlePool<Packet> m_pool;
    std::deque<int> m_packets;
    
public:
    void Reset()
    {
        m_pool.Reset();
        m_packets.clear();
    }

    void Push(size_t size, const byte_t* bytes)
    {
        int handle = m_pool.Alloc();
        auto& packet = m_pool.RefObject(handle);
        packet.Assign(size, bytes);
        m_packets.push_back(handle);
    }

    bool Peek(size_t& outSize, const byte_t*& outBytes)
    {
        if (m_packets.empty())
            return false;

        int handle = m_packets.front();
        auto& packet = m_pool.RefObject(handle);
        outSize = packet.GetSize();
        outBytes = packet.GetBytes();
        return true;
    }

    void Pop()
    {
        assert(!m_packets.empty());
        int handle = m_packets.front();
        m_packets.pop_front();
        m_pool.Free(handle);
    }

    bool IsEmpty()
    {
        return m_packets.empty();
    }
};


EL_NAMESPACE_END()
