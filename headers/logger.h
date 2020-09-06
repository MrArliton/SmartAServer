#include <stdint.h>
#include <string>
#include <vector>
#include <stdio.h>
#include "mutex"
#include <ctime>
namespace log{

static std::vector<std::string> paths;
static uint16_t level_logs = 1;
static std::mutex syn_log; 
static uint16_t error = -1;
static uint8_t log_active = true;
static std::string error_string;
// level 1 - Errors
// level 2 - Details
// level 3 - Many Details
// level 4 - Secure Level
void setLevelLog(uint16_t level){
    level_logs = level;
}
uint16_t bindPathLog(std::string path){ // Saving path and return index path
    paths.push_back(path);
    return paths.size()-1;
}
void clearPathsBind(){
        paths.clear();
}
uint16_t getErrorLog(){
    syn_log.lock();
    uint16_t er = error;
    error = -1;
    syn_log.unlock();
    return er;
}
void setActiveLog(uint8_t active){
    syn_log.lock();
    log_active = active;
    syn_log.unlock();
}
uint16_t printLogFile(std::string args,std::string info_class,std::string info_m,uint16_t index_path,uint16_t level_log){ 
    syn_log.lock();
    if(log_active){
    FILE *file;
    if(level_log<=level_logs){
    time_t time = std::time(0);
    tm *ltm = localtime(&time);
    std::string date = "C_"+info_class; 
    date +="-D_"+std::to_string(ltm->tm_mday); // Day
     date+="-T_"+std::to_string(ltm->tm_hour); // Hours
     date+=":"+std::to_string(ltm->tm_min); // Hours
      date+=":"+std::to_string(ltm->tm_sec); // Seconds
    try{
        file = fopen(paths.at(index_path).c_str(),"a"); 
        if(file){
            // format [Class][data][info of message][message][\n]
            if(!fwrite(date.c_str(),date.size(),1,file)){ // There get error with write
                error = 203;
            }
            if(!fwrite(("--"+info_m+":").c_str(),info_m.size()+2,1,file)){ // There get error with write
                error = 203;
            }
            if(!fwrite(("--"+info_m+":").c_str(),info_m.size()+2,1,file)){ // There get error with write
                error = 203;
            }
            if(!fwrite(args.c_str(),args.size(),1,file)){ // There get error with write
                error = 203;
            }
            fwrite("\n",sizeof("\n")-1,1,file);
        }
        fclose(file);
    }catch(std::exception exc){
        error = 201;
        error_string = exc.what();
    }
    }
    
    }
    syn_log.unlock();
}  

}
