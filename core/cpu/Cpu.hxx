#ifndef GOOBER_CPU_HXX
#define GOOBER_CPU_HXX

#include <filesystem>
#include <map>

#include "opfuncs.hxx"
#include "../mmu/Mmu.hpp"

#include <Definitions.hpp>

namespace fs = std::filesystem;

namespace goober {
    
    class Cpu {
    private:
        struct Operation {
            opfunc    function;
            void*     funcArgs;
            byte      clockCycles;
        };

        struct Register {
            byte hiByte;
            byte loByte;
            
            word fullWord() {
                return (hiByte << 8) & loByte; 
            }
        };

        Register    regAF;
        Register    regBC;
        Register    regDE;
        Register    regHL;
        word        stackPointer;
        word        programCounter;
        MMU*        mmu;

        std::map<OpCode, Operation> cpuOps;

        /**
         * LDr1_r2 loads the value of r2 into r1. 
        */
        void LDr1_r2(const char& reg1, const char& reg2);

        /**
         * LDr1_hlMem loads the value located at the address pointed to by 
         * the HL register into the specified register.
        */
        void LDr1_hlMem(const char& reg, const char& not_used);

        /**
         * LDhlMem_val loads the requested value into the memory at the address
         * pointed to by HL. 
        */
        void LDhlMem_val(const char& reg, const char& not_used);
    public:
        Cpu();
        ~Cpu();

        void run(const fs::path& romPath);
    };
};

#endif // GOOBER_CPU_HXX