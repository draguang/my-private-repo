#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    
    
    Vtop* top = new Vtop;
    
    
    const int TEST_CYCLES = 10;
    
    for (int i = 0; i < TEST_CYCLES; i++) {
        int a = rand() & 1;
        int b = rand() & 1;
        
        top->a = a;
        top->b = b;
        top->eval(); 
        
        printf("a = %d, b = %d, f = %d\n", a, b, top->f);
        assert(top->f == (a ^ b));
    }
    return 0;
}


