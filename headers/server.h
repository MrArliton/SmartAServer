#pragma once
#include "client.h"
#include <vector>
#include "const.h"

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
        // log
        uint16_t log_index; 
        void printlog(std::string mes,uint16_t level,bool error);
// Поток
void static listen_clients(Server* arg_s){
    struct sockaddr_in addr;
    uint32_t len = sizeof(addr);
    while(arg_s->listen_on){
    arg_s->syn_lis.unlock();
    uint32_t client_desc = accept(arg_s->server_descript,(sockaddr*)&addr,&len);
    if(client_desc==-1){
    arg_s->error = 102;
    return;
    }
    Client* client = new Client(client_desc,&addr);
    arg_s->clients.push_back(client);
    if(client->start()==-1){
        arg_s->error = 102;
        client->~Client();
        arg_s->clients.pop_back(); // Erase client
        delete client;
        return;
 
    }   
    arg_s->syn_lis.lock(); // Guard listen_on
    }
};
    public:
        Server(const uint16_t port,uint16_t size_queue);
        uint16_t start_listeting();
        uint16_t stop_listeting();
        uint16_t disconnect_all();
        ~Server();
};