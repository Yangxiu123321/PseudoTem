#ifndef __PSEUDO_TEM_H
#define __PSEUDO_TEM_H

#include <pthread.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <set>
#include <map>



class PseudoTem{
protected:
    PseudoTem(){
        pthread_mutex_init(&mutexIn,NULL);
        initTerminal();
        memset(&oldCfg,0,sizeof(oldCfg));
    }
public:
    static PseudoTem* getInstance(void);
    void initTerminal(void);
    void releaseTerminal(void);
    void run(void);
    void initCmdMap(void);

private:
    static pthread_mutex_t mutexIn;
    static PseudoTem *__instance;
    static std::map<std::string,std::set<std::string>> cmdMap;
    struct termios oldCfg;
    cc_t vmin;
    cc_t vtime;
};

#endif
