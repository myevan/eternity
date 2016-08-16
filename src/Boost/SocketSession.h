#pragma once

#include <Core/Defines.h>
#include <Core/Types.h>

#include <Core/Buffer.h>
#include <Core/PacketQueue.h>
#include <Core/TextPacketParser.h>

#include <boost/asio.hpp>

EL_NAMESPACE()

using boost::asio::ip::tcp;

class SocketSession : public std::enable_shared_from_this<SocketSession>
{
private:
    Buffer m_readingBuf;
    std::shared_ptr<PacketQueue> m_packetQueue;

private:
    tcp::socket m_socket;

public:
    SocketSession(tcp::socket socket)
    : m_socket(std::move(socket))
    {
        m_packetQueue = std::make_shared<PacketQueue>(); 
        m_readingBuf.Reserve(8 * 1024);
    }

    virtual ~SocketSession()
    {
    }

    void Start()
    {
        Read();
    }

    void Write(size_t size, const byte_t* bytes)
    {
        auto self(shared_from_this());

        int bufHandle;
        auto& buf = AllocWritingBuffer(size, bytes, bufHandle);
        boost::asio::async_write(m_socket, boost::asio::buffer(buf.GetBytes(), buf.GetSize()), [this, self, &bufHandle](const boost::system::error_code& error, size_t transferredSize)
        {
            FreeWritingBuffer(bufHandle);
        });
    }

private:
    void Read()
    {
        auto self(shared_from_this());

        auto slackSize = m_readingBuf.GetSlackSize();
        auto* slackBytes = m_readingBuf.GetSlackBytes();
        m_socket.async_read_some(boost::asio::buffer(slackBytes, slackSize), [this, self](const boost::system::error_code& error, size_t transferredSize)
        {
            if (error)
            {
                printf("error:%s\n", error.message().c_str());
            }
            else
            {
                m_readingBuf.AddSize(transferredSize);

                auto readingSize = m_readingBuf.GetSize();
                auto* readingBytes = m_readingBuf.GetBytes();
                
                auto& packetParser = GetPacketParser();
                auto& packetQueue = GetPacketQueue();
                auto parsingSize = packetParser.Parse(readingSize, readingBytes, packetQueue);
                size_t packetSize;
                const byte_t* packetBytes;
                while (packetQueue.Peek(packetSize, packetBytes))
                {
                    OnRead(packetSize, packetBytes);
                    packetQueue.Pop();
                }

                m_readingBuf.RemoveHead(parsingSize);

                Read();
            }
        });
    }

protected:
    void OnRead(size_t packetSize, const byte_t* packetBytes)
    {
        if (0 < packetSize)
        {
            printf("read %d:%s", (int)packetSize, (const char*)packetBytes);
        }
    }

protected:
    virtual Buffer& AllocWritingBuffer(size_t size, const byte_t* bytes, int& outHandle)
    {
        auto& pool = GetWritingBufferPool();
        int handle = pool.Alloc();
        auto& buf = pool.RefObject(handle);
        buf.Assign(size, bytes);
        outHandle = handle;
        return buf;
    }

    virtual void FreeWritingBuffer(int handle)
    {
        auto& pool = GetWritingBufferPool();
        pool.Free(handle);
    }

    virtual PacketParser& GetPacketParser()
    {
        static TextPacketParser packetParser;
        return packetParser;
    }

    virtual PacketQueue& GetPacketQueue()
    {
        return *m_packetQueue;
    }

private:
    static HandlePool<Buffer>& GetWritingBufferPool()
    {
        static HandlePool<Buffer> s_pool;
        return s_pool;
    }

};

EL_NAMESPACE_END()
