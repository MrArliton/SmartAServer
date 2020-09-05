#include <stdint.h>
#include <vector>
namespace log{
static std::vector<uint8_t*> paths;
static uint16_t level_logs = 1;
// level 1 - Errors
// level 2 - Details
// level 3 - Many Details
// level 4 - Secure Level
void setLevelLog(uint16_t level){
    level_logs = level;
}
uint16_t bindPathLog(const uint8_t* path){ // Saving path and return index path
    uint8_t* buff;
    uint32_t len = 0;
    while(true){
        if(path[len]){
            len+=1;
        }else{
            break;
        }
    }
    buff = new uint8_t(len);
    for(int i = 0;i< len;i++){
        buff[i] = path[i];
    }
    paths.push_back(buff);
    return paths.size()-1; 
}
void clearPathsBind(){
    for(int i = 0;i<paths.size();i++){
        delete[]paths.at(i);
    }
}
void clearPathBind(uint16_t index){
    delete[]paths.at(index);
}
uint16_t printLogFile(std::vector<const uint8_t*> args,uint16_t index_path,uint16_t level_logs){ 

}
}
