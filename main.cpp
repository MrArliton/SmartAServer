#include <iostream>
#include "headers/server.h"
#include "headers/logger.h"
int main(int argc,const char* argv[]){
    Server sv(1111,5);
    sv.start_listeting();
    while(true){
    }
    return 0;
}