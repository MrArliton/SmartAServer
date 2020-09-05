#include "headers/client.h"

Client::Client(uint32_t socket_descript,struct sockaddr_in* addr){
this->socket_descript = new uint32_t();
this->error = new uint16_t();
this->addr_c = new sockaddr_in();
//
*this->addr_c = *addr;
*this->socket_descript = socket_descript;
*error = -1;
};
uint16_t Client::send_c(const uint8_t* buffer, uint32_t size){
    if(send(*socket_descript,buffer,size,0)==-1){
        *error = 10;
        return -1;
    }
    return 1;
};
uint16_t Client::start(){
    send_c((uint8_t*)"Hello",sizeof("Hello"));
};
uint16_t Client::recv_c(uint8_t* buffer,uint16_t size){
    if(recv(*socket_descript,buffer,size,0)==-1){
            *error = 11;
        return -1;
    }
    return 1;
};
Client::~Client(){
    close(*socket_descript);
    delete this->socket_descript;
    delete this->error;
};