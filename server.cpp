#include "headers/server.h"

Server::Server(const uint16_t port,uint16_t size_queue){
    server_descript = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    // Binding server
    if(bind(server_descript,(struct sockaddr *)&addr,sizeof(addr))==-1){
        error = 100;
    }   
    if(listen(server_descript,size_queue)==-1){

        error = 101;
    }
};
uint16_t Server::start_listeting(){ // Start thread listening
    listen_on = true;
    listen_thread = std::thread(listen_clients,this);
    listen_thread.detach();
};
uint16_t Server::stop_listeting(){ // stop thread listening
    syn_lis.lock();
    listen_on = false;
    syn_lis.unlock();
};
uint16_t Server::disconnect_all(){ 
    for(int i = 0; i<clients.size();i++){
        clients.at(i)->~Client();
        delete clients.at(i);
    }
    return 1;
};
Server::~Server(){
    disconnect_all();
    close(server_descript);
};
