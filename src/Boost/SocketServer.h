#pragma once

#include "SocketFactory.h"

EL_NAMESPACE()

using boost::asio::ip::tcp;

class SocketServer : public std::enable_shared_from_this<SocketServer>
{
private:
    tcp::acceptor m_acceptor;
    tcp::socket m_socket;

private:
    std::shared_ptr<SocketFactory> m_factory;

public:
    SocketServer(boost::asio::io_service& service, int port)
    : m_acceptor(service, tcp::endpoint(tcp::v4(), port))
    , m_socket(service)
    , m_factory(std::make_shared<SocketFactory>())
    {
    }

    bool Start()
    {
        AcceptSocket();

        return true;
    }

private:
    void AcceptSocket()
    {
        auto self(shared_from_this());

        m_acceptor.async_accept(m_socket, [this, self](const boost::system::error_code& error)
        {
            auto& factory = GetFactory();
            auto session = factory.CreateSession(std::move(m_socket));
            session->Start();

            AcceptSocket();
        });
    }

private:
    SocketFactory& GetFactory()
    {
        return *m_factory;
    }
};

EL_NAMESPACE_END()
