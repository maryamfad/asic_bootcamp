#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>


void check_result(
        Valu* alu,
        int A,
        int B,
        int op,
        int expected,
        const std:: string name
    )
    {
        alu->A = A;
        alu->B = B;
        alu->op = op;

        alu->eval();

        if(alu->Y != expected){
            std::cout << name << " FAILED. Expected"
                        << expected
                        << " Got "
                        << (int)alu->Y
                        << std::endl;
        }
        else{
            std::cout << name << " PASSED\n";
        }
    }


int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    Valu* alu=new Valu;

    int errors = 0;
    constexpr int ADD = 0;
    constexpr int SUB = 1;
    constexpr int AND = 2;
    constexpr int OR  = 3;
    constexpr int XOR = 4;
    constexpr int NOT = 5;
    constexpr int SHL = 6;
    constexpr int SHR = 7;
    Verilated::traceEverOn(true);

    VerilatedVcdC* tfp = new VerilatedVcdC;

    alu->trace(tfp, 99);

    tfp->open("waves/alu_wave.vcd");

    
    check_result(alu, 15, 1, ADD, 16, "ADD");
    check_result(alu, 20, 5, SUB, 15, "SUB");
    check_result(alu, 0b1100, 0b1010, AND, 0b1000, "AND");
    check_result(alu, 0b1100, 0b1010, OR, 0b1110, "OR");
    check_result(alu, 0b1100, 0b1010, XOR, 0b0110, "XOR");
    check_result(alu, 0b00001111, 0, NOT, 0b11110000, "NOT");
    check_result(alu, 0b00001111, 0, SHL, 0b00011110, "SHIFT LEFT");
    check_result(alu, 0b00001110, 0, SHR, 0b00000111, "SHIFT RIGHT");

    
    tfp->close();

    if(errors == 0)
        std::cout << "ALL TESTS PASSED\n";
    else
        std::cout << errors << "TESTS FAILED\n";

    delete tfp;
    delete alu;

    return errors;

}