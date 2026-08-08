 #include "Vregister.h"
 #include "verilated.h"
 #include "verilated_vcd_c.h"
 
 #include <iostream>
 #include <iomanip>

 vluint64_t sim_time = 0;
 int errors = 0;

 void tick(Vregister* reg, VerilatedVcdC* tfp)
 {
    reg->clk = 0;
    reg->eval();
    tfp->dump(sim_time++);

    reg->clk =1;
    reg->eval();
    tfp->dump(sim_time++);

    reg->clk = 0;
    reg->eval();
    tfp->dump(sim_time++);
 }

 void check_result(
    Vregister* reg,
    int expected,
    const std::string& name
 )
 {
    if(reg->Q != expected){
        std::cout
            << name
            << " FAILED. Expected 0x"
            << std::hex
            << expected
            << " Got 0x"
            << (int)reg->Q
            << std::dec
            << std::endl;

        errors++;
    }
    else{
        std::cout
            << name
            << " Passed"
            << std::endl;
    }
 }

 int main(int argc, char** argv)
 {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    Vregister* reg = new Vregister;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    reg->trace(tfp,99);
    tfp->open("waves/register_wave.vcd");

    //Test Reset
    reg->rst = 1;
    reg->en = 0;
    reg->D = 0x55;

    tick(reg, tfp);

    check_result(reg,0x00, "RESET");

    //Test Load AA
    reg->rst = 0;
    reg->en = 1;
    reg->D = 0xAA;

    tick(reg, tfp);

    check_result(reg, 0xAA, "LOAD AA");

    //Test Hold
    reg->en = 0;
    reg->D = 0x55;

    tick(reg, tfp);

    check_result(reg, 0xAA, "HOLD");

    //Test Load 33
    reg->en = 1;
    reg->D = 0x33;

    tick(reg, tfp);

    check_result(reg, 0x33, "LOAD 33");


    tfp->close();
    delete tfp;
    delete reg;

    if(errors == 0)
        std::cout << "\nALL TESTS PASSED\n";
    else
        std::cout << "\n" << errors << " TESTS FAILED\n";

    return errors;
 }