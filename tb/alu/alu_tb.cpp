#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>

int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    Valu* alu=new Valu;

    int errors = 0;

    Verilated::traceEverOn(true);

    VerilatedVcdC* tfp = new VerilatedVcdC;

    alu->trace(tfp, 99);

    tfp->open("waves/alu_wave.vcd");

    //Test Add
    alu->A=15;
    alu->B=1;
    alu->op=0b000;

    alu->eval();

    if(alu->Y != 16)
    {
        std::cout << "ADD FAILED\n";
        errors++;
    }

    //Test SUB
    alu->A=20;
    alu->B=3;
    alu->op=0b001;

    alu->eval();

    if(alu->Y != 17){
        std::cout << "SUB FAILED\n";
        errors++;
    }

    //Test AND
    alu->A=0b1100;
    alu->B=0b1010;
    alu->op = 0b010;

    alu->eval();

    if(alu->Y != 0b1000){
        std::cout << "AND FAILED\n";
        errors++;
    }

    tfp->close();

    if(errors == 0)
        std::cout << "ALL TESTS PASSED\n";
    else
        std::cout << errors << "TESTS FAILED\n";

    delete tfp;
    delete alu;

    return errors;

}