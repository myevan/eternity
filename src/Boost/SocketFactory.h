#pragma once

#include "SocketSession.h"

EL_NAMESPACE()

using boost::asio::ip::tcp;

class SocketFactory
{
public:
    virtual std::shared_ptr<SocketSession> CreateSession(tcp::socket socket)
    {
        return std::make_shared<SocketSession>(std::move(socket));
    }
};

EL_NAMESPACE_END()
