#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated.h"
#include <nvboard.h>

void nvboard_bind_all_pins(Vtop* top);
Vtop* top = new Vtop;

void single_cycle() {
  top->clk = 0; top->eval();
  top->clk = 1; top->eval();
}

void reset(int n) {
  top->rst = 1;
  while (n -- > 0) single_cycle();
  top->rst = 0;
}

int main(int argc, char** argv)
{
    
    Verilated::commandArgs(argc, argv);
    nvboard_bind_all_pins(top);
    nvboard_init();
    reset(10);  
    while(1) 
    {
        nvboard_update();
        if(top->clk == 1||top->rst == 1)
          single_cycle();
        nvboard_update();
    }
}