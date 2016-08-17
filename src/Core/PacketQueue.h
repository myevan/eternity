#pragma once

#include "SharedPool.h"
#include "Packet.h"

EL_NAMESPACE()

class PacketQueue
{
private:
    std::deque<PacketPtr> m_packets;
    
public:
    virtual ~PacketQueue()
    {
        Reset();
    }

    void Reset()
    {
        if (!m_packets.empty())
        {
            auto& pool = GetPacketPool();
            for (auto& packet: m_packets)
            {
                packet->Reset();
                pool.Free(packet);
            }
            m_packets.clear();
        }
    }

    void Push(size_t size, const byte_t* bytes)
    {
        auto& pool = GetPacketPool();
        auto packet = pool.Alloc();
        packet->Assign(size, bytes);
        m_packets.push_back(packet);
    }

    bool Peek(size_t& outSize, const byte_t*& outBytes)
    {
        if (m_packets.empty())
            return false;

        auto& packet = m_packets.front();
        outSize = packet->GetSize();
        outBytes = packet->GetBytes();
        return true;
    }

    void Pop()
    {
        assert(!m_packets.empty());
        
        auto packet = m_packets.front();
        m_packets.pop_front();

        auto& pool = GetPacketPool();
        pool.Free(packet);
    }

    bool IsEmpty()
    {
        return m_packets.empty();
    }

protected:
    virtual SharedPool<Packet>& GetPacketPool()
    {
        static SharedPool<Packet> s_pool;
        return s_pool;
    }
};


EL_NAMESPACE_END()
