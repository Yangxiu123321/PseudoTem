#include "PseudoTem.hpp"
#include <cstddef>
#include <ostream>
#include <pthread.h>
#include <stdio.h>
#include <string>
#include <termios.h>
#include <iostream>

PseudoTem *PseudoTem::__instance = nullptr;
pthread_mutex_t PseudoTem::mutexIn;
std::map<std::string, std::set<std::string>> PseudoTem::cmdMap;

PseudoTem *PseudoTem::getInstance(void) {
    if (__instance == nullptr) {
        pthread_mutex_lock(&mutexIn);
        if (__instance == nullptr)
        __instance = new PseudoTem();
        pthread_mutex_unlock(&mutexIn);
    }
    return __instance;
}

void PseudoTem::initCmdMap(void) {
    cmdMap.insert(
        {"fix", std::set<std::string>({"-r", "-s", "-b", "-t", "-d", "-w"})});
    cmdMap.insert({"cap", std::set<std::string>({"-t", "save"})});
    cmdMap.insert({"help", std::set<std::string>({""})});
    cmdMap.insert({"net", std::set<std::string>({"-i"})});
    cmdMap.insert({"delay", std::set<std::string>({"-a", "-b"})});
    cmdMap.insert({"relay", std::set<std::string>({"-c"})});
}

void PseudoTem::initTerminal(void) {
    if (tcgetattr(0, &oldCfg) < 0){
        perror("tcsetattr()");
    }
    // //取消标准模式。标准模式：允许使用特殊字符并按行缓冲
    oldCfg.c_lflag &= ~ICANON;
    // old.c_lflag &= ~ECHO;
    vmin = oldCfg.c_cc[VMIN];
    vtime = oldCfg.c_cc[VTIME];
    // resd()读多少字节返回
    oldCfg.c_cc[VMIN] = 1;
    // timeoue
    oldCfg.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &oldCfg) < 0){
        perror("tcsetattr ICANON");
    }

}

void *handleFun(void *args) {
    std::string line;
    PseudoTem *term = PseudoTem::getInstance();
    term->initTerminal();
    term->initTerminal();
    // 提高输入速度
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    std:: cout << "> " << std::flush;
    for(;;) {
        // Lterm::command(line);
        // char buf = 0;
        // read(0,&buf,1);
        //putchar(buf);

        // 不能输出空格
        std::cin >> line;

        // 不能输出删除键backspace
        // std::getline(std::cin,line);

        // 此处写处理函数


        // std::cout << line <<std::endl;
        std::cout << "> " << std::flush;
    }
}

void PseudoTem::run() {
    pthread_t nid;
    pthread_create(&nid, NULL, handleFun, NULL);
}

void PseudoTem::releaseTerminal(void) {
    oldCfg.c_lflag |= ICANON;
    // old.c_lflag |= ECHO;
    oldCfg.c_cc[VMIN] = vmin;
    oldCfg.c_cc[VTIME] = vtime;
    if (tcsetattr(0, TCSANOW, &oldCfg) < 0){
        perror("tcsetattr ~ICANON");
    }
  // TCSADRAIN
}
