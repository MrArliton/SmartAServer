#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>
class Client
{
private:
    uint32_t *socket_descript = 0;
public:
    Client(uint32_t socket_descript); // Creating client with accept server
    uint16_t send(uint8_t* buffer,uint32_t size); 
    uint16_t recv(uint8_t* buffer,uint16_t size);    
    ~Client();
}