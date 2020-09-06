#pragma once
#include "logger.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdint.h>
#include <thread>
#include <mutex>

class Client    
{
private:
    uint32_t *socket_descript = 0;
    uint16_t* error; // Error code
    struct sockaddr_in* addr_c; 
    std::thread thread_loop;
public:
    Client(uint32_t socket_descript,struct sockaddr_in* addr); // Creating client with accept server
    uint16_t start(); // get mode -> client do authorize
    uint16_t send_c(const uint8_t* buffer,uint32_t size); 
    uint16_t recv_c(uint8_t* buffer,uint16_t size);    
    ~Client();
};