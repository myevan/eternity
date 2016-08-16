#include <Boost/SocketServer.h>

#include <boost/asio.hpp>

int main()
{
    using namespace EL;

    boost::asio::io_service service;

    auto server = std::make_shared<SocketServer>(service, 5000);
    server->Start();

    service.run();

    return 0;
}
