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
    std::shared_ptr<Buffer> m_readingBuf;
    std::shared_ptr<PacketQueue> m_packetQueue;

private:
    tcp::socket m_socket;

public:
    SocketSession(tcp::socket socket)
    : m_socket(std::move(socket))
    {
        m_packetQueue = GetPacketQueuePool().Alloc(); 
        m_readingBuf = GetReadingBufferPool().Alloc();
    }

    virtual ~SocketSession()
    {
        GetReadingBufferPool().Free(m_readingBuf);
        GetPacketQueuePool().Free(m_packetQueue);
    }

    void Start()
    {
        auto& readingBuf = GetReadingBuffer();
        readingBuf.Reserve(8 * 1024);
        Read();
    }

    void Write(size_t size, const byte_t* bytes)
    {
        auto self(shared_from_this());

        auto writingBuf = GetWritingBufferPool().Alloc();
        writingBuf->Assign(size, bytes);

        boost::asio::async_write(m_socket, boost::asio::buffer(writingBuf->GetBytes(), writingBuf->GetSize()), [this, self, writingBuf](const boost::system::error_code& error, size_t transferredSize)
        {
            GetWritingBufferPool().Free(writingBuf);
        });
    }

private:
    void Read()
    {
        auto self(shared_from_this());

        auto& readingBuf = GetReadingBuffer();
        auto slackSize = readingBuf.GetSlackSize();
        auto* slackBytes = readingBuf.GetSlackBytes();
        m_socket.async_read_some(boost::asio::buffer(slackBytes, slackSize), [this, self](const boost::system::error_code& error, size_t transferredSize)
        {
            if (error)
            {
                printf("error:%s\n", error.message().c_str());
            }
            else
            {
                auto& readingBuf = GetReadingBuffer();
                readingBuf.AddSize(transferredSize);

                auto readingSize = readingBuf.GetSize();
                auto* readingBytes = readingBuf.GetBytes();
                
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

                readingBuf.RemoveHead(parsingSize);

                Read();
            }
        });
    }

protected:
    void OnRead(size_t packetSize, const byte_t* packetBytes)
    {
        if (0 < packetSize && packetSize < 256)
        {
            char buf[256 + 1];
            memcpy(buf, packetBytes, packetSize);
            buf[packetSize] = '\0';
            printf("read %d:[%s]\n", (int)packetSize, buf);
        }
    }

protected:
    virtual PacketParser& GetPacketParser()
    {
        static TextPacketParser packetParser;
        return packetParser;
    }

    virtual PacketQueue& GetPacketQueue()
    {
        return *m_packetQueue;
    }

    virtual Buffer& GetReadingBuffer()
    {
        return *m_readingBuf;
    }

private:
    static SharedPool<PacketQueue>& GetPacketQueuePool()
    {
        static SharedPool<PacketQueue> s_pool;
        return s_pool;
    }

    static SharedPool<Buffer>& GetReadingBufferPool()
    {
        static SharedPool<Buffer> s_pool;
        return s_pool;
    }

    static SharedPool<Buffer>& GetWritingBufferPool()
    {
        static SharedPool<Buffer> s_pool;
        return s_pool;
    }

};

EL_NAMESPACE_END()
