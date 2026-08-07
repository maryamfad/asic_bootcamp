#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>


void check_result(
        Valu* alu,
        int A,
        int B,
        int op,
        int expected_Y,
        int expected_carry,
        int expected_zero,
        int expected_overflow,
        const std:: string& name
    )
    {
        alu->A = A;
        alu->B = B;
        alu->op = op;

        alu->eval();

        bool pass = true;

        if(alu->Y != expected_Y)
        {
            pass = false;
            std::cout << name 
                  << " Y FAILED. Expected "
                  << expected_Y
                  << " Got "
                  << (int)alu->Y
                  << std::endl;
        }

        if(alu->carry != expected_carry){
            pass = false;
            std::cout << name
                <<"CARRY FAILED"
                <<std::endl;
        }

        if(alu->zero != expected_zero){
            pass = false;
            std::cout << name
                <<"ZERO FAILED"
                <<std::endl;
        }

        if(alu->overflow != expected_overflow){
            pass = false;
            std::cout << name
                << "OVERFLOW FAILED"
                << std::endl;
        }

        if (pass){
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

    
    // Basic ALU operation tests
    check_result(alu, 15,         1,          ADD, 16,         0, 0, 0, "ADD");
    check_result(alu, 20,         3,          SUB, 17,         0, 0, 0, "SUB");
    check_result(alu, 0b1100,     0b1010,     AND, 0b1000,     0, 0, 0, "AND");
    check_result(alu, 0b1100,     0b1010,     OR,  0b1110,     0, 0, 0, "OR");
    check_result(alu, 0b1100,     0b1010,     XOR, 0b0110,     0, 0, 0, "XOR");
    check_result(alu, 0b00001111, 0,          NOT, 0b11110000, 0, 0, 0, "NOT");
    check_result(alu, 0b00001111, 0,          SHL, 0b00011110, 0, 0, 0, "SHIFT LEFT");
    check_result(alu, 0b00001110, 0,          SHR, 0b00000111, 0, 0, 0, "SHIFT RIGHT");

    // Flag tests
    check_result(alu, 255, 1, ADD,   0,   1, 1, 0, "ADD CARRY");
    check_result(alu, 127, 1, ADD, 128,   0, 0, 1, "ADD OVERFLOW");
    check_result(alu,   5, 5, SUB,   0,   0, 1, 0, "SUB ZERO");

    
    tfp->close();

    if(errors == 0)
        std::cout << "ALL TESTS PASSED\n";
    else
        std::cout << errors << "TESTS FAILED\n";

    delete tfp;
    delete alu;

    return errors;

}