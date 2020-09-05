#pragma once
#include "client.h"
#include <vector>

class Server{
    private:
        struct sockaddr_in addr;
        uint32_t server_descript;
        uint16_t error; // Error code
        std::vector<Client*> clients;
        std::thread listen_thread;
        //
        uint8_t listen_on = false;
        std::mutex syn_lis;
        //
        void listen_clients();
    public:
        Server(const uint16_t port,uint16_t size_queue);
        uint16_t start_listeting();
        uint16_t stop_listeting();
        uint16_t disconnect_all();
        ~Server();
};