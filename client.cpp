#include "client.h"


Client::Client(uint32_t socket_descript){
this->socket_descript = new uint32_t();
*this->socket_descript = socket_descript;
}
uint16_t Client::send(uint8_t* buffer, uint32_t size){


}
uint16_t Client::recv(uint8_t* buffer,uint16_t size){

 
}
Client::~Client(){
    close(*socket_descript);
    delete this->socket_descript;
}