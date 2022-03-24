#include <iostream>
#include <unistd.h>
#include "PseudoTem.hpp"

int main(void){
  PseudoTem* term = PseudoTem::getInstance();
  term->run();

  for(;;){
    sleep(1);
  }
  return 0;
}
