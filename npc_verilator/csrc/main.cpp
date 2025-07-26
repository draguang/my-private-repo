#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated.h"
#include <nvboard.h>
#include "verilated_vcd_c.h"
void nvboard_bind_all_pins(Vtop* top);
VerilatedContext *context = new VerilatedContext;
Vtop* top = new Vtop{context};

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
    context->commandArgs(argc,argv);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    context->traceEverOn(true);
    top->trace(tfp,0);
    tfp->open("wave.vcd");
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
        tfp->dump(context->time());
        context->timeInc(1);
    }
    tfp->close();
}